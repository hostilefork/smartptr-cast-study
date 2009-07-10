/* GCC4.4 Compiler detection */ 
/* http://stackoverflow.com/questions/435708/any-way-in-cmake-to-require-gcc-version-4 */

#if __GNUC__ != 4
#error "Requires GCC 4.4 or greater for unique_ptr support"
#endif

#if __GNUC_MINOR__ < 4
#error "Requires GCC 4.4 or greater for unique_ptr support"
#endif

int main() { return 0; }

