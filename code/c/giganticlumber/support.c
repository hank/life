// First, a subroutine that substitutes any instance of cBad with
// cGood in a string.  This is used to replace the plus sign with
// a space character.

void SwapChar(char * pOriginal, char cBad, char cGood) {
    int i;    // generic counter variable

    // Loop through the input string (cOriginal), character by
    // character, replacing each instance of cBad with cGood

    i = 0;
    while (pOriginal[i]) {
        if (pOriginal[i] == cBad) pOriginal[i] = cGood;
        i++;
    }
}

// Now, a subroutine that unescapes escaped characters.
static int IntFromHex(char *pChars) {
    int Hi;        // holds high byte
    int Lo;        // holds low byte
    int Result;    // holds result

    // Get the value of the first byte to Hi

    Hi = pChars[0];
    if ('0' <= Hi && Hi <= '9') {
        Hi -= '0';
    } else
    if ('a' <= Hi && Hi <= 'f') {
        Hi -= ('a'-10);
    } else
    if ('A' <= Hi && Hi <= 'F') {
        Hi -= ('A'-10);
    }

    // Get the value of the second byte to Lo

    Lo = pChars[1];
    if ('0' <= Lo && Lo <= '9') {
        Lo -= '0';
    } else
    if ('a' <= Lo && Lo <= 'f') {
        Lo -= ('a'-10);
    } else
    if ('A' <= Lo && Lo <= 'F') {
        Lo -= ('A'-10);
    }
    Result = Lo + (16 * Hi);
    return (Result);
}

// And now, the main URLDecode() routine.  The routine loops
// through the string pEncoded, and decodes it in place. It checks
// for escaped values, and changes all plus signs to spaces. The
// result is a normalized string.  It calls the two subroutines
// directly above in this listing.

void URLDecode(unsigned char *pEncoded) {
    char *pDecoded;          // generic pointer

    // First, change those pesky plusses to spaces
    SwapChar (pEncoded, '+', ' ');

    // Now, loop through looking for escapes
    pDecoded = pEncoded;
    while (*pEncoded) {
        if (*pEncoded=='%') {
            // A percent sign followed by two hex digits means
            // that the digits represent an escaped character.
            // We must decode it.

            pEncoded++;
            if (isxdigit(pEncoded[0]) && isxdigit(pEncoded[1])) {
                *pDecoded++ = (char) IntFromHex(pEncoded);
                pEncoded += 2;
            }
        } else {
            *pDecoded ++ = *pEncoded++;
        }
    }
    *pDecoded = '\0';
}
