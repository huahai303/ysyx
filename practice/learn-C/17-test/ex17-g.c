#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct Address {
    int id;
    int set;
    char *name;
    char *email;
		char *phone;
};

struct Database {
		int max_data;
		int max_rows;
    struct Address *rows;
};

struct Connection {
    FILE *file;
    struct Database *db;
};

struct Connection *g_conn = NULL;
void Database_close();

void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
		Database_close();
    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s %s\n",
            addr->id, addr->name, addr->email, addr->phone);
}

void Database_load()
{
    int rc = fread(&g_conn->db->max_rows, sizeof(int), 1, g_conn->file);
    if(rc != 1) die("Failed to load max_rows.");
		rc = fread(&g_conn->db->max_data, sizeof(int), 1, g_conn->file);
		if(rc != 1) die("Failed to load max_data.");
		
		g_conn->db->rows = calloc(g_conn->db->max_rows, sizeof(struct Address));
		if(!g_conn->db->rows) die("Memory error");
		
		int i = 0;
		for(i = 0; i < g_conn->db->max_rows; i++)
		{
				struct Address *addr = &g_conn->db->rows[i];
				rc = fread(&addr->id, sizeof(int), 1, g_conn->file);
				if(rc != 1) die("Failed to load id.");
				rc = fread(&addr->set, sizeof(int), 1, g_conn->file);
				if(rc != 1) die("Failed to load set.");

				addr->name = malloc(g_conn->db->max_data);
				addr->email = malloc(g_conn->db->max_data);
				addr->phone = malloc(g_conn->db->max_data);
				if(!addr->name || !addr->email || !addr->phone)	die("Memory error");
				rc = fread(addr->name, g_conn->db->max_data, 1, g_conn->file);
				if(rc != 1) die("Failed to load name.");
				rc = fread(addr->email, g_conn->db->max_data, 1, g_conn->file);
				if(rc != 1) die("Failed to load email.");
				rc = fread(addr->phone, g_conn->db->max_data, 1, g_conn->file);
				if(rc != 1) die("Failed to load phone.");
		}
}

void Database_open(const char *filename, char mode, int max_rows, int max_data)
{
    g_conn = malloc(sizeof(struct Connection));
    if(!g_conn) die("Memory error");
		g_conn->file = NULL;
		g_conn->db = NULL;
    
		g_conn->db = malloc(sizeof(struct Database));
    if(!g_conn->db) die("Memory error");
		g_conn->db->rows = NULL;
	
    if(mode == 'c') 
		{
        g_conn->file = fopen(filename, "w");
    		if(g_conn->file)
				{
								g_conn->db->max_data = max_data;
								g_conn->db->max_rows = max_rows;
				}
								
		}
	 	else {
        g_conn->file = fopen(filename, "r+");

        if(g_conn->file) {
            Database_load(g_conn);
        }
    }

    if(!g_conn->file) die("Failed to open the file");

}

void Database_close()
{
    if(g_conn) 
		{
        if(g_conn->file) fclose(g_conn->file);
        if(g_conn->db)
				{
						if(g_conn->db->rows)
						{
								for(int i = 0; i < g_conn->db->max_rows; i++)
								{
										free(g_conn->db->rows[i].name);
										free(g_conn->db->rows[i].email);
										free(g_conn->db->rows[i].phone);
								}
								free(g_conn->db->rows);
						}
						free(g_conn->db);
				}
				free(g_conn);
    }
}

void Database_write()
{
    rewind(g_conn->file);
		
		fwrite(&g_conn->db->max_rows, sizeof(int), 1, g_conn->file);
		fwrite(&g_conn->db->max_data, sizeof(int), 1, g_conn->file);
		
		for(int i = 0; i < g_conn->db->max_rows; i++)
		{
				struct Address *addr = &g_conn->db->rows[i];
				fwrite(&addr->id, sizeof(int), 1, g_conn->file);
				fwrite(&addr->set, sizeof(int), 1, g_conn->file);

				fwrite(addr->name, g_conn->db->max_data, 1, g_conn->file);
				fwrite(addr->email, g_conn->db->max_data, 1, g_conn->file);
				fwrite(addr->phone, g_conn->db->max_data, 1, g_conn->file);
		}
		int rc = fflush(g_conn->file);
		if(rc == -1) die("Cannot flush data"); 
}

void Database_create()
{
    g_conn->db->rows = malloc(sizeof(struct Address) * g_conn->db->max_rows);
		if(!g_conn->db->rows) die("Memory error");
		int i = 0;

    for(i = 0; i < g_conn->db->max_rows; i++) {
        // make a prototype to initialize it
        struct Address *addr = &g_conn->db->rows[i];
        addr->id = i;
				addr->set = 0;

				addr->name = calloc(g_conn->db->max_data,1);
				addr->email = calloc(g_conn->db->max_data,1);
				addr->phone = calloc(g_conn->db->max_data,1);
				if(!addr->name || !addr->email || !addr->phone) die("Memory error");
    }
}

void Database_set(int id, const char *name, const char *email, const char *phone)
{
    struct Address *addr = &g_conn->db->rows[id];
    if(addr->set) die("Already set, delete it first");

    addr->set = 1;
    // WARNING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name, g_conn->db->max_data);
		addr->name[g_conn->db->max_data - 1] = '\0';
    // demonstrate the strncpy bug
    if(!res) die("Name copy failed");

    res = strncpy(addr->email, email, g_conn->db->max_data);
		addr->email[g_conn->db->max_data - 1] = '\0'; 
    if(!res) die("Email copy failed");

		res = strncpy(addr->phone, phone, g_conn->db->max_data);
		addr->phone[g_conn->db->max_data - 1] = '\0';
		if(!res) die("Phone copy failed");
}

void Database_get(int id)
{
    struct Address *addr = &g_conn->db->rows[id];

    if(addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set");
    }
}

void Database_find(char *information)
{
    if(information == NULL)
				die("Information is empty");
		struct Address *addr = g_conn->db->rows;
		int found = 0;
    for(int i = 0; i < g_conn->db->max_rows; i++)
		{
				if(addr[i].set)
				{
						if(strcmp(addr[i].email,information) == 0)
						{
								Address_print(&addr[i]);
								found = 1;
						}
						else if(strcmp(addr[i].name,information) == 0)
						{
								Address_print(&addr[i]);
								found = 1;		
						}
						else if(strcmp(addr[i].phone,information) == 0)
						{
								Address_print(&addr[i]);
								found = 1;
						}
				}
		}
		if(!found)
				printf("Cannot find information\n");
}
void Database_delete(int id)
{
    struct Address *addr = &g_conn->db->rows[id];
    addr->set = 0;
		addr->id = id;
		memset(addr->name, 0, g_conn->db->max_data);
		memset(addr->email, 0, g_conn->db->max_data);
		memset(addr->phone, 0, g_conn->db->max_data);
}

void Database_list()
{
    int i = 0;
    struct Database *db = g_conn->db;

    for(i = 0; i < db->max_rows; i++) {
        struct Address *cur = &db->rows[i];

        if(cur->set) {
            Address_print(cur);
        }
    }
}
int main(int argc, char *argv[])
{
    if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");

    char *filename = argv[1];
    char action = argv[2][0];
		int max_rows = 100;
		int max_data = 512;
		if(action == 'c' && argc >= 5)
		{
				max_rows = atoi(argv[3]);
				max_data = atoi(argv[4]);
		}
  	Database_open(filename, action, max_rows, max_data);
		int id = 0;
		if(argc > 3 && action != 'c' && action != 'f') id = atoi(argv[3]);
		
		if(id >= g_conn->db->max_rows) die("There's not that many records.");
    switch(action) {
        case 'c':
            Database_create();
            Database_write();
            break;

        case 'g':
            if(argc != 4) die("Need an id to get");
            Database_get(id);
            break;

        case 's':
            if(argc != 7) die("Need id, name, email, phone to set");
            Database_set(id, argv[4], argv[5], argv[6]);
            Database_write();
            break;

        case 'd':
            if(argc != 4) die("Need an id to delete");
            Database_delete(id);
            Database_write();
            break;

        case 'l':
            Database_list();
            break;
				case 'f':
						Database_find(argv[3]);
						break;
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close();

    return 0;
}
