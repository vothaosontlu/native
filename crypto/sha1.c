#include "../crypto.h"
#include <openssl/sha.h>
#include "../general.h"
#include "../string.h"

/**
 *
 * @param target
 * @return
 */
char *sha1_encode(unsigned char *target) {

    unsigned char digest[SHA_DIGEST_LENGTH];
    int length_target = length_pointer_char(target);

    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, target, length_target);
    SHA1_Final(digest, &ctx);

    char mdString[SHA_DIGEST_LENGTH * 2 + 1];
    int index;
    for (index ; index < SHA_DIGEST_LENGTH; ++index) {
        sprintf(&mdString[index * 2], "%02x", (unsigned int) digest[index]);
    }

    char *result = string_copy(mdString);
    return result;
}

//**
// *
// * @param target
// * @return
// */
//unsigned char *sha1_decode(const char *target) {
//    return "";
//}