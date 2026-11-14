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

void Database_close(struct Connection *conn);

void die(const char *message, struct Connection *conn)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
		Database_close(conn);
    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s %s\n",
            addr->id, addr->name, addr->email, addr->phone);
}

void Database_load(struct Connection *conn)
{
    int rc = fread(&conn->db->max_rows, sizeof(int), 1, conn->file);
    if(rc != 1) die("Failed to load max_rows.",conn);
		rc = fread(&conn->db->max_data, sizeof(int), 1, conn->file);
		if(rc != 1) die("Failed to load max_data.",conn);
		
		conn->db->rows = calloc(conn->db->max_rows, sizeof(struct Address));
		if(!conn->db->rows) die("Memory error",conn);
		
		int i = 0;
		for(i = 0; i < conn->db->max_rows; i++)
		{
				struct Address *addr = &conn->db->rows[i];
				rc = fread(&addr->id, sizeof(int), 1, conn->file);
				if(rc != 1) die("Failed to load id.",conn);
				rc = fread(&addr->set, sizeof(int), 1, conn->file);
				if(rc != 1) die("Failed to load set.",conn);

				addr->name = malloc(conn->db->max_data);
				addr->email = malloc(conn->db->max_data);
				addr->phone = malloc(conn->db->max_data);
				if(!addr->name || !addr->email || !addr->phone)	die("Memory error",conn);
				rc = fread(addr->name, conn->db->max_data, 1, conn->file);
				if(rc != 1) die("Failed to load name.",conn);
				rc = fread(addr->email, conn->db->max_data, 1, conn->file);
				if(rc != 1) die("Failed to load email.",conn);
				rc = fread(addr->phone, conn->db->max_data, 1, conn->file);
				if(rc != 1) die("Failed to load phone.",conn);
		}
}

struct Connection *Database_open(const char *filename, char mode, int max_rows, int max_data)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if(!conn) die("Memory error",conn);
		conn->file = NULL;
		conn->db = NULL;
    
		conn->db = malloc(sizeof(struct Database));
    if(!conn->db) die("Memory error",conn);
		conn->db->rows = NULL;
	
    if(mode == 'c') 
		{
        conn->file = fopen(filename, "w");
    		if(conn->file)
				{
								conn->db->max_data = max_data;
								conn->db->max_rows = max_rows;
				}
								
		}
	 	else {
        conn->file = fopen(filename, "r+");

        if(conn->file) {
            Database_load(conn);
        }
    }

    if(!conn->file) die("Failed to open the file",conn);

    return conn;
}

void Database_close(struct Connection *conn)
{
    if(conn) 
		{
        if(conn->file) fclose(conn->file);
        if(conn->db)
				{
						if(conn->db->rows)
						{
								for(int i = 0; i < conn->db->max_rows; i++)
								{
										free(conn->db->rows[i].name);
										free(conn->db->rows[i].email);
										free(conn->db->rows[i].phone);
								}
								free(conn->db->rows);
						}
						free(conn->db);
				}
				free(conn);
    }
}

void Database_write(struct Connection *conn)
{
    rewind(conn->file);
		
		fwrite(&conn->db->max_rows, sizeof(int), 1, conn->file);
		fwrite(&conn->db->max_data, sizeof(int), 1, conn->file);
		
		for(int i = 0; i < conn->db->max_rows; i++)
		{
				struct Address *addr = &conn->db->rows[i];
				fwrite(&addr->id, sizeof(int), 1, conn->file);
				fwrite(&addr->set, sizeof(int), 1, conn->file);

				fwrite(addr->name, conn->db->max_data, 1, conn->file);
				fwrite(addr->email, conn->db->max_data, 1, conn->file);
				fwrite(addr->phone, conn->db->max_data, 1, conn->file);
		}
		int rc = fflush(conn->file);
		if(rc == -1) die("Cannot flush data",conn); 
}

void Database_create(struct Connection *conn)
{
    conn->db->rows = malloc(sizeof(struct Address) * conn->db->max_rows);
		if(!conn->db->rows) die("Memory error",conn);
		int i = 0;

    for(i = 0; i < conn->db->max_rows; i++) {
        // make a prototype to initialize it
        struct Address *addr = &conn->db->rows[i];
        addr->id = i;
				addr->set = 0;

				addr->name = calloc(conn->db->max_data,1);
				addr->email = calloc(conn->db->max_data,1);
				addr->phone = calloc(conn->db->max_data,1);
				if(!addr->name || !addr->email || !addr->phone) die("Memory error",conn);
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email, const char *phone)
{
    struct Address *addr = &conn->db->rows[id];
    if(addr->set) die("Already set, delete it first",conn);

    addr->set = 1;
    // WARNING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name, conn->db->max_data);
		addr->name[conn->db->max_data - 1] = '\0';
    // demonstrate the strncpy bug
    if(!res) die("Name copy failed",conn);

    res = strncpy(addr->email, email, conn->db->max_data);
		addr->email[conn->db->max_data - 1] = '\0'; 
    if(!res) die("Email copy failed",conn);

		res = strncpy(addr->phone, phone, conn->db->max_data);
		addr->phone[conn->db->max_data - 1] = '\0';
		if(!res) die("Phone copy failed",conn);
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];

    if(addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set",conn);
    }
}

void Database_find(struct Connection *conn, char *information)
{
    if(information == NULL)
				die("Information is empty",conn);
		struct Address *addr = conn->db->rows;
		int found = 0;
    for(int i = 0; i < conn->db->max_rows; i++)
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
void Database_delete(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];
    addr->set = 0;
		addr->id = id;
		memset(addr->name, 0, conn->db->max_data);
		memset(addr->email, 0, conn->db->max_data);
		memset(addr->phone, 0, conn->db->max_data);
}

void Database_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;

    for(i = 0; i < db->max_rows; i++) {
        struct Address *cur = &db->rows[i];

        if(cur->set) {
            Address_print(cur);
        }
    }
}
int main(int argc, char *argv[])
{
    if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]", NULL);

    char *filename = argv[1];
    char action = argv[2][0];
		int max_rows = 100;
		int max_data = 512;
		if(action == 'c' && argc >= 5)
		{
				max_rows = atoi(argv[3]);
				max_data = atoi(argv[4]);
		}
  	struct Connection *conn = Database_open(filename, action, max_rows, max_data);
		int id = 0;
		if(argc > 3 && action != 'c' && action != 'f') id = atoi(argv[3]);
		
		if(id >= conn->db->max_rows) die("There's not that many records.",conn);
    switch(action) {
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if(argc != 4) die("Need an id to get", conn);
            Database_get(conn, id);
            break;

        case 's':
            if(argc != 7) die("Need id, name, email, phone to set", conn);
            Database_set(conn, id, argv[4], argv[5], argv[6]);
            Database_write(conn);
            break;

        case 'd':
            if(argc != 4) die("Need an id to delete", conn);
            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;
				case 'f':
						Database_find(conn, argv[3]);
						break;
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list", conn);
    }

    Database_close(conn);

    return 0;
}
