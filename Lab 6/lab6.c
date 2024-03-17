#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef long long ll;

// Helper function to get the signed value of a number given its bitwidth
int64_t get_signed_value(int64_t value, int bitwidth)
{
    int64_t mask = (1LL << (bitwidth - 1)) - 1;
    int64_t sign_mask = 1LL << (bitwidth - 1);
    int64_t sign_extend = -(value & sign_mask);
    return (value & mask) | sign_extend;
}

ll signed_min(int bitwidth)
{
    int64_t min_value = 1LL << (bitwidth - 1);
    return get_signed_value(min_value, bitwidth);
}

ll signed_max(int bitwidth)
{
    int64_t max_value = (1LL << (bitwidth - 1)) - 1;
    return get_signed_value(max_value, bitwidth);
}

ll sat_add(ll operand1, ll operand2, int bitwidth)
{
    ll max_value = signed_max(bitwidth);
    ll sum = operand1 + operand2;
    if (!(max_value >= sum))
    {
        return operand1 | operand2;
    }
    return sum;
}

ll sat_sub(ll operand1, ll operand2, int bitwidth)
{
    ll diff = operand1 - operand2;
    ll min = signed_min(bitwidth);
    ll max = signed_max(bitwidth);
    
    int underflow = !(signed_min(bitwidth) <= diff && diff <= signed_max(bitwidth));

    diff &= ~underflow;

    int wrong_sign = (operand1 ^ operand2) < 0 && (diff ^ operand1) < 0;

    diff |= wrong_sign & (operand1 > 0 ? max : min);

    return diff;
}

int main(int argc, char *argv[])
{
    int bitwidth = atoi(argv[1]);
    int operator= atoi(argv[4]);
    ll result;
    if (argc == 2)
    {
        bitwidth = atoi(argv[1]);
        printf("%d-bit signed integer range\n", bitwidth);
        printf("min: %lld \t 0x%016llx\n", signed_min(bitwidth), signed_min(bitwidth));
        printf("max: %lld \t 0x%016llx\n", signed_max(bitwidth), signed_max(bitwidth));
    }
    if (argc == 5)
    {
        ll operand1 = atoll(argv[2]);
        ll operand2 = atoll(argv[3]);

        if (operator== 0) // ADDITION
        {
            result = sat_add(operand1, operand2, bitwidth);
            printf("%lld + %lld = %lld\n", operand1, operand2, result);
        }
        else if (operator== 1) // SUBTRACTION
        {
            result = sat_sub(operand1, operand2, bitwidth);
            printf("%lld - %lld = %lld\n", operand1, operand2, result);
        }
        else
        {
            printf("Invalid operator: %d. Must be 0 (for addition) or 1 (for subtraction).\n", operator);
            return 1;
        }
    }
    return 0;
}