#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

/* Adapted from exercise 17 */

struct Address {
  int id;
  int set;
  char *name;
  char *email;
  char *about;
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

struct Connection *conn;

void Database_close()
{
  if (conn) {

    if (conn->file)
      fclose(conn->file);

    if (conn->db) {
      if (conn->db->rows) {
        int i = 0;
        for (i = 0; i < conn->db->max_rows; i++) {
          struct Address *cur = &conn->db->rows[i];
          if (cur->name != NULL)
            free(cur->name);
          if (cur->email != NULL)
            free(cur->email);
          if (cur->about != NULL)
            free(cur->about);
        }
        free(conn->db->rows);
      }
      free(conn->db);
    }

    free(conn);
  }
}

void die(const char *message)
{
  if (errno)
    perror(message);
  else
    printf("ERROR: %s\n", message);

  Database_close(conn);

  exit(1);
}

void Database_load()
{
  /*
  int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
  if (rc != 1)
    die("Failed to load the database.");
  */
  fread(&conn->db->max_rows, sizeof(int), 1, conn->file);
  fread(&conn->db->max_data, sizeof(int), 1, conn->file);

  conn->db->rows = malloc(sizeof(struct Address) * conn->db->max_rows);

  //rc = fread(conn->db->rows, sizeof(struct Address), conn->db->max_rows, conn->file);

  int i = 0;
  for (i = 0; i < conn->db->max_rows; i++) {
    //fwrite(&conn->db->rows[i], sizeof(struct Address), conn->db->max_rows, conn->file);
    struct Address *addr = &conn->db->rows[i];
    addr->name = malloc(sizeof(char) * conn->db->max_data);
    addr->email = malloc(sizeof(char) * conn->db->max_data);
    addr->about = malloc(sizeof(char) * conn->db->max_data);

    fread(&addr->id, sizeof(int), 1, conn->file);
    fread(&addr->set, sizeof(int), 1, conn->file);
    fread(addr->name, sizeof(char) * conn->db->max_data, 1, conn->file);
    fread(addr->email, sizeof(char) * conn->db->max_data, 1, conn->file);
    fread(addr->about, sizeof(char) * conn->db->max_data, 1, conn->file);
  }
  /*
  if (rc != 1)
    die("Failed to load the database. [1]");
  */
}

void Database_open(const char *filename, char mode)
{
  conn = malloc(sizeof(struct Connection));
  if (!conn)
    die("Memory error");

  conn->db = malloc(sizeof(struct Database));
  if (!conn->db)
    die("Memory error");

  if (mode == 'c') {
    conn->file = fopen(filename, "w");
  } else {
    conn->file = fopen(filename, "r+");

    if (conn->file) {
      Database_load();
    }
  }

  if (!conn->file)
    die("Failed to open the file");
}


void Database_write()
{
  rewind(conn->file);

  //int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
  fwrite(&conn->db->max_rows, sizeof(int), 1, conn->file);
  fwrite(&conn->db->max_data, sizeof(int), 1, conn->file);
  /*
  if (rc != 1)
    die("Failed to write database.");
  */
  int i = 0;
  for (i = 0; i < conn->db->max_rows; i++) {
    //fwrite(&conn->db->rows[i], sizeof(struct Address), conn->db->max_rows, conn->file);
    struct Address *addr = &conn->db->rows[i];
    fwrite(&addr->id, sizeof(int), 1, conn->file);
    fwrite(&addr->set, sizeof(int), 1, conn->file);
    fwrite(addr->name, sizeof(char) * conn->db->max_data, 1, conn->file);
    fwrite(addr->email, sizeof(char) * conn->db->max_data, 1, conn->file);
    fwrite(addr->about, sizeof(char) * conn->db->max_data, 1, conn->file);
  }
  /*
  rc = fflush(conn->file);
  if (rc == -1)
    die("Cannot flush database.");
  */
}

void Database_create(int max_rows, int max_data)
{
  conn->db->max_rows = max_rows;
  conn->db->max_data = max_data;
  conn->db->rows = malloc(sizeof(struct Address) * max_rows);
  int i = 0;
  for (i = 0; i < max_rows; i++) {
    struct Address addr = {
      .id = i,
      .set = 0,
      .name=malloc(sizeof(char) * max_data),
      .email=malloc(sizeof(char) * max_data),
      .about=malloc(sizeof(char) * max_data)
    };
    conn->db->rows[i] = addr;
  }
}

void Database_set(int id, const char *name, const char *email, const char *about)
{
  struct Address *addr = &conn->db->rows[id];
  if (addr->set)
    die("Already set, delete it first!");

  addr->set = 1;

  char *res = strncpy(addr->name, name, conn->db->max_data);
  if (!res)
    die("Name copy failed");
  res = strncpy(addr->email, email, conn->db->max_data);
  if (!res)
    die("Email copy failed");

  res = strncpy(addr->about, about, conn->db->max_data);
  if (!res)
    die("'About' copy failed");

  addr->name[conn->db->max_data - 1] = '\0';
  addr->email[conn->db->max_data - 1] = '\0';
  addr->about[conn->db->max_data - 1] = '\0';
}

void Address_print(struct Address *addr)
{
  printf("%d %s %s %s\n", addr->id, addr->name, addr->email, addr->about);
}

void Database_get(int id)
{
  struct Address *cur = &conn->db->rows[id];
  if (cur->set) {
    Address_print(cur);
  } else {
    die("ID is not set");
  }
}

void Database_list()
{
  int i = 0;
  for (i = 0; i < conn->db->max_rows; i++) {
    struct Address *cur = &conn->db->rows[i];

    if (cur->set) {
      Address_print(cur);
    }
  }
}

void Database_find(const char *search_term)
{
  for (int i = 0; i < conn->db->max_rows; i++) {
    struct Address *cur = &conn->db->rows[i];
    if (strstr(cur->name, search_term) || strstr(cur->email, search_term) || strstr(cur->about, search_term))
      Address_print(cur);
  }
}


int main(int argc, char *argv[])
{
  if (argc < 3) {
    printf("usage: ./database <dbfile> <action> [params]\n");
    printf("\tdatabase <dbfile> create <max rows> <max data per field>\n");
    printf("\tdatabase <dbfile> get <id>\n");
    printf("\tdatabase <dbfile> set <id> <name> <email>\n");
    printf("\tdatabase <dbfile> list\n");
    printf("\tdatabase <dbfile> find <term>\n");
    die("too few arguments supplied!");
  }

  char *filename = argv[1];
  char action = argv[2][0];
  Database_open(filename, action);

  switch (action) {
    case 'c':
      if (argc == 5) {
        int max_rows = atoi(argv[3]);
        int max_data = atoi(argv[4]);
        Database_create(max_rows, max_data);
        Database_write();
      } else {
        printf("minidb <db filename> c <max row> <max data>\n");
        die("incorrect arguments to create new database!");
      }
      break;
    case 'g':
      if (argc != 4)
        die("Need an ID to get");
      Database_get(atoi(argv[3]));
      break;
    case 's':
      if (argc != 7)
        die("Need id, name, email, about to set");
      if (atoi(argv[3]) >= conn->db->max_rows)
        die("not enough space for that id!");
      Database_set(atoi(argv[3]), argv[4], argv[5], argv[6]);
      Database_write();
      break;
    case 'l':
      Database_list(conn);
      break;
    case 'f':
      Database_find(argv[3]);
      break;
    default:
      die("Invalid action: c=create, g=get, s=set, d=del, l=list");
  }
  Database_close();
  return 0;
  
}
