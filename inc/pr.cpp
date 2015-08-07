
/**
 * With probability d return true and with 1-d return false.
 */
bool random_bool(double d, unsigned int *seed)
{
    if (d==0)
    {
        return false;
    }
    return RAND_MAX*d >= rand_r(seed);
}
