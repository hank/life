/* GiganticLumber */

#include <gpgme.h>   /* gpgme             */
#include <stdio.h>   /* printf            */
#include <unistd.h>  /* write             */
#include <errno.h>   /* errno             */
#include <locale.h>  /* locale support    */

#define SIZE 1024

/* USE -D_FILE_OFFSET_BITS=64 (at least) on Debian!  */

int main()
{
   char *p;
   char buf[SIZE];
   size_t read_bytes;
   int tmp;
   gpgme_ctx_t ceofcontext;
   gpgme_error_t err;
   gpgme_data_t wdata, rdata;
   gpgme_import_result_t import_result;
   gpgme_key_t key;
   gpgme_user_id_t uid;
   gpgme_key_sig_t sig;
   gpgme_engine_info_t enginfo;

   /* The function `gpgme_check_version' must be called before any other
    * function in the library, because it initializes the thread support
    * subsystem in GPGME. (from the info page) */
   setlocale (LC_ALL, "");
   p = (char *) gpgme_check_version(NULL);
   printf("version=%s\n",p);
   /* set locale, because tests do also */
   gpgme_set_locale(NULL, LC_CTYPE, setlocale (LC_CTYPE, NULL));

   /* check for OpenPGP support */
   err = gpgme_engine_check_version(GPGME_PROTOCOL_OpenPGP);
   if(err != GPG_ERR_NO_ERROR) return 1;

   p = (char *) gpgme_get_protocol_name(GPGME_PROTOCOL_OpenPGP);
   printf("Protocol name: %s\n",p);

   /* get engine information */
   err = gpgme_get_engine_info(&enginfo);
   if(err != GPG_ERR_NO_ERROR) return 2;
   printf("file=%s, home=%s\n",enginfo->file_name,enginfo->home_dir);

   /* create our own context */
   err = gpgme_new(&ceofcontext);
   if(err != GPG_ERR_NO_ERROR) return 3;

   /* set protocol to use in our context */
   err = gpgme_set_protocol(ceofcontext,GPGME_PROTOCOL_OpenPGP);
   if(err != GPG_ERR_NO_ERROR) return 4;

   /* set engine info in our context; I changed it for ceof like this:

   err = gpgme_ctx_set_engine_info (ceofcontext, GPGME_PROTOCOL_OpenPGP,
               "/usr/bin/gpg","/home/user/nico/.ceof/gpg/");

      but I'll use standard values for this example: */

   err = gpgme_ctx_set_engine_info (ceofcontext, GPGME_PROTOCOL_OpenPGP,
               enginfo->file_name,enginfo->home_dir);
   if(err != GPG_ERR_NO_ERROR) return 5;

   /* do ascii armor data, so output is readable in console */
   gpgme_set_armor(ceofcontext, 1);
   
   /* create buffer for data exchange with gpgme*/
   err = gpgme_data_new(&rdata);
   if(err != GPG_ERR_NO_ERROR) return 6;

   /* Open a key file and create a data pointer */
   err = gpgme_data_new_from_file(&rdata, "/tmp/hank.gpg", 1);

   /* set encoding for the buffer... */
   err = gpgme_data_set_encoding(rdata,GPGME_DATA_ENCODING_ARMOR);
   if(err != GPG_ERR_NO_ERROR) return 7;

   /* verify encoding */
   tmp = gpgme_data_get_encoding(rdata);
   if(tmp == GPGME_DATA_ENCODING_ARMOR) {
      printf("encode ok\n");
   } else {
      printf("encode broken\n");
   }

   err = gpgme_set_keylist_mode(ceofcontext, GPGME_KEYLIST_MODE_SIGS);

   /* Import the key */
   err = gpgme_op_import(ceofcontext, rdata);
   if(err != GPG_ERR_NO_ERROR) return 8;

   import_result = gpgme_op_import_result(ceofcontext);
   printf("Key %s Imported\n", import_result->imports[0].fpr);

   err = gpgme_get_key(ceofcontext, import_result->imports[0].fpr,
      &key, 0);
   if(err != GPG_ERR_NO_ERROR) return 9;

   uid = key->uids;
   if(!uid) return 10;

   do {
     printf("Found UID: %s\n", uid->uid);
     sig = uid->signatures;
     if(!sig) return 11;
     do {
       printf("Found SIG: %s\n", sig->keyid);
     } while((sig = sig->next) != NULL);
   } while((uid = uid->next) != NULL);
   /* with NULL it exports all public keys */
   //err = gpgme_op_export(ceofcontext,NULL,0,data);
   //if(err != GPG_ERR_NO_ERROR) return 8;

   //read_bytes = gpgme_data_seek (data, 0, SEEK_END);
   //printf("end is=%d\n",read_bytes);
   //if(read_bytes == -1) {
   //   p = (char *) gpgme_strerror(errno);
   //   printf("data-seek-err: %s\n",p);
   //   return 9;
   //}
   //read_bytes = gpgme_data_seek (data, 0, SEEK_SET);
   //printf("start is=%d (should be 0)\n",read_bytes);

   /* write keys to stderr */
   //while ((read_bytes = gpgme_data_read (data, buf, SIZE)) > 0) {
   //   write(2,buf,read_bytes);
   //}
   /* append \n, so that there is really a line feed */
   //write(2,"\n",1);

   /* free data */
   gpgme_data_release(rdata);

   /* free context */
   gpgme_release(ceofcontext);

   return 0;
}
