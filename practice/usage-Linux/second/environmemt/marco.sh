marco(){
	MARCO_DIR=$(pwd)
	echo "current path : $MARCO_DIR"
}

polo(){
	if [ -n "$MARCO_DIR" ]; then
					cd $MARCO_DIR
					echo "get it"
	else
					echo "error"
	fi
}

