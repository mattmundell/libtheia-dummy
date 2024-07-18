#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void
fr (void *p) {
  if (p)
    free (p);
}

static void
set_license (const char *str) {
  FILE *f;

  f = fopen ("/tmp/libtheia-dummy-license", "w");
  if (f) {
    fwrite (str, strlen (str), 1, f);
    fclose (f);
  }
}

static const char *
get_license () {
  FILE *f;

  f = fopen ("/tmp/libtheia-dummy-license", "r");
  if (f) {
    long fsize;
    char *lic;

    fseek (f, 0, SEEK_END);
    fsize = ftell (f);
    fseek (f, 0, SEEK_SET);

    lic = malloc (fsize + 1);
    fread (lic, fsize, 1, f);
    fclose (f);

    lic[fsize] = 0;

    return lic;
  }

  // create
  {
    const char *str;

    str = "some sort of license string";
    set_license (str);
    return strdup (str);
  }

  return strdup ("ERR");
}

void
theia_license_free (theia_license_t *lic) {
  if (lic) {
    if (lic->meta) {
      fr (lic->meta->id);
      fr (lic->meta->version);
      fr (lic->meta->comment);
      fr (lic->meta->type);
      fr (lic->meta->customer_name);
      fr (lic->meta);
    }

    if (lic->appliance) {
      fr (lic->appliance->model);
      fr (lic->appliance->model_type);
      fr (lic->appliance);
    }

    if (lic->keys) {
      fr (lic->keys->feed);
      fr (lic->keys);
    }

    if (lic->signatures) {
      fr (lic->signatures->license);
      fr (lic->signatures);
    }

    fr (lic);
  }
}

// caller will free() ret
theia_client_t *
theia_client_new_mqtt (theia_client_t **ret) {
  theia_client_t *tc;

  tc = calloc (1, 1);
  if (ret)
    *ret = tc;
  return tc;
}

int
theia_client_connect (theia_client_t *cl, const char *broker) {
  return 0;
}

int
theia_new_get_license_cmd (theia_get_license_cmd_t **cmd) {
  if (cmd) {
    *cmd = calloc (1, sizeof (theia_get_license_cmd_t));
    (*cmd)->message = calloc (1, sizeof (theia_message_t));
  }
  return 0;
}

void
theia_get_license_cmd_free (theia_get_license_cmd_t *cmd) {
}

int
theia_new_modify_license_cmd (char *content, theia_modify_license_cmd_t **cmd) {
  if (cmd) {
    *cmd = calloc (1, sizeof (theia_modify_license_cmd_t));
    (*cmd)->message = calloc (1, sizeof (theia_message_t));
    if (content) {
      (*cmd)->license = strdup (content);

      // should be done in theia_client_send_cmd
      set_license (content);
    }
  }
  return 0;
}

void
theia_modify_license_cmd_free (theia_modify_license_cmd_t *cmd) {
}

void
theia_client_disconnect (theia_client_t *cl) {
}

int
theia_client_send_cmd (theia_client_t *cl, int some_sort_of_id, theia_cmd_t *cmd) {
  if (cmd) {
    if (cmd->message == NULL)
      cmd->message = calloc (1, sizeof (theia_message_t));
    cmd->message->id = strdup ("200");
    cmd->message->group_id = strdup ("SOME_GROUP_ID");
  }
  return 0;
}

int
theia_client_get_info_response (theia_client_t *cl, int some_sort_of_id, const char *name1, const char *name2, const char *group_id, theia_info_t **info, theia_info_t **fail) {
  if (fail)
    *fail = NULL;

  if (info) {
    if (strcmp (name1, "got.license") == 0) {
      theia_got_license_info_t *linfo;
      theia_license_t *lic;

      linfo = calloc (1, sizeof (*linfo));

      linfo->status = strdup ("200");

      linfo->message = calloc (1, sizeof (*linfo->message));
      linfo->message->id = strdup ("200");
      linfo->message->group_id = strdup (group_id ?: "SOME_GROUP_ID");

      lic = calloc (1, sizeof (*linfo->license));
      linfo->license = lic;

      lic->meta = calloc (1, sizeof (*lic->meta));
      lic->meta->id = strdup ("ID");
      lic->meta->version = strdup ("1.0");
      lic->meta->comment = strdup ("This is a comment.");
      lic->meta->type = strdup ("TYPE");
      lic->meta->customer_name = strdup ("Jazz");
      lic->meta->created = time (NULL);
      lic->meta->begins = time (NULL);
      lic->meta->expires = time (NULL);

      lic->appliance = calloc (1, sizeof (*lic->appliance));
      lic->appliance->model = strdup ("Model9");
      lic->appliance->model_type = strdup ("Type11");
      lic->appliance->sensor = 1; // boolean

      lic->keys = calloc (1, sizeof (*lic->keys));
      lic->keys->feed = strdup ("key for feed.... probably long stretch of text");

      lic->signatures = calloc (1, sizeof (*lic->signatures));
      lic->signatures->license = strdup (get_license ());

      *info = (theia_info_t *) linfo;
    }

    if (strcmp (name1, "modified.license") == 0) {
      *info = calloc (1, sizeof (*info));

      (*info)->status = strdup ("200");

      (*info)->message = calloc (1, sizeof ((*info)->message));
      (*info)->message->id = strdup ("200");
      (*info)->message->group_id = strdup (group_id ?: "SOME_GROUP_ID");
    }
  }

  return 0;
}

void
theia_got_license_info_free (theia_got_license_info_t *info) {
  if (info) {
    fr (info->status);

    if (info->message) {
      fr (info->message->id);
      fr (info->message->group_id);
      fr (info->message);
    }

    theia_license_free (info->license);
  }
}

void
theia_modified_license_info_free (theia_modified_license_info_t *info) {
}

void
theia_failure_modify_license_info_free (theia_failure_modify_license_info_t *info) {
}
