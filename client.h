#include <time.h>

typedef struct {
  char *id;
  char *group_id;
} theia_message_t;

typedef struct {
  char *id;
  char *version;
  char *comment;
  char *type;
  char *customer_name;
  time_t created;
  time_t begins;
  time_t expires;
} theia_license_meta_t;

typedef struct {
  char *model;
  char *model_type;
  int sensor;
} theia_license_appliance_t;

typedef struct {
  char *feed;
} theia_license_keys_t;

typedef struct {
  char *license;
} theia_license_signatures_t;

typedef struct {
  theia_license_meta_t *meta;
  theia_license_appliance_t *appliance;
  theia_license_keys_t *keys;
  theia_license_signatures_t *signatures;
} theia_license_t;

typedef struct {
  theia_message_t *message;
} theia_get_license_cmd_t;

typedef struct {
  theia_message_t *message;
  char *license;
} theia_modify_license_cmd_t;
    
typedef struct {
} theia_modified_license_info_t;

typedef struct {
  char *error;
} theia_failure_modify_license_info_t;

typedef enum
{
  THEIA_LICENSE_INFO_TOPIC,
  THEIA_LICENSE_CMD_TOPIC
} theia_fix_this;

typedef struct {
} theia_client_t;

typedef struct {
  theia_message_t *message;
} theia_cmd_t;

typedef struct {
  char *status;
  theia_message_t *message;
} theia_info_t;

typedef struct {
  char *status;
  theia_message_t *message;
  theia_license_t *license;
} theia_got_license_info_t;

void
theia_license_free (theia_license_t *);

// caller will free() ret
theia_client_t *
theia_client_new_mqtt (theia_client_t **);

int
theia_client_connect (theia_client_t *, const char *);

int
theia_new_get_license_cmd (theia_get_license_cmd_t **);

void
theia_get_license_cmd_free (theia_get_license_cmd_t *);

int
theia_new_modify_license_cmd (char *, theia_modify_license_cmd_t **);

void
theia_modify_license_cmd_free (theia_modify_license_cmd_t *);

void
theia_client_disconnect (theia_client_t *);

int
theia_client_send_cmd (theia_client_t *, int, theia_cmd_t *);

int
theia_client_get_info_response (theia_client_t *, int, const char *, const char *, const char *, theia_info_t **, theia_info_t **);

void
theia_got_license_info_free (theia_got_license_info_t *);

void
theia_modified_license_info_free (theia_modified_license_info_t *);

void
theia_failure_modify_license_info_free (theia_failure_modify_license_info_t *);
