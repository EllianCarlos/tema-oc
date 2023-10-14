DATABASE_DIR=./db
DATABASE_BINARIES_DIR=./db/bin
DATABASE_DOWNLOAD_LIST=$(DATABASE_DIR)/list_file.txt
DATABASE_DOWNLOAD_SCRIPT=$(DATABASE_DIR)/pdb_batch_download.sh

.PHONY: clean download-db unpack-download

download-db:
	sh $(DATABASE_DOWNLOAD_SCRIPT) -f $(DATABASE_DOWNLOAD_LIST) -p -o $(DATABASE_BINARIES_DIR)

unpack-download: 
	gzip -d ./$(DATABASE_BINARIES_DIR)/*.gz	

