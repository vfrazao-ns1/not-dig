#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "../src/dns/dns.h"

// Defines to allow for unit testing
#define FAIL() printf(" failure in %s() line %d\n", __func__, __LINE__)
#define _assert(test)                              \
    do                                             \
    {                                              \
        total_tests++;                             \
        printf("%d. %s: ", total_tests, __func__); \
        if (!(test))                               \
        {                                          \
            printf("- ");                          \
            FAIL();                                \
            tests_failed++;                        \
        }                                          \
        else                                       \
            printf("+\n");                         \
        last_result = NOERROR;                     \
    } while (0)

int test_domain_encoding_1(void);
int test_domain_encoding_2(void);
int test_domain_encoding_3(void);
int test_domain_encoding_4(void);
int test_domain_encoding_5(void);
int test_domain_encoding_6(void);
int test_domain_encoding_7(void);
int test_domain_encoding_8(void);
int test_domain_encoding_9(void);
int test_domain_encoding_10(void);
int test_domain_decoding_1(void);
int test_domain_decoding_2(void);
int test_header_generation_1(void);
int test_header_generation_2(void);
int test_header_generation_3(void);
int test_header_generation_4(void);
int test_question_generation_1(void);
int test_question_generation_2(void);
int test_question_generation_3(void);
int test_question_generation_4(void);
int test_question_generation_5(void);
int test_answer_wire_uncompressed_1(void);
int test_answer_wire_uncompressed_2(void);
int test_answer_wire_uncompressed_3(void);
int test_answer_wire_uncompressed_4(void);
int test_query_wire_uncompressed_1(void);
int test_array_count_1(void);
int test_array_count_2(void);
int test_packet_generation_perf_1(void);
int test_bytes_to_header_1(void);
int test_bytes_to_header_2(void);
int test_bytes_to_question_1(void);
int test_bytes_to_question_2(void);
int test_bytes_to_rr_1(void);
int test_bytes_to_rr_2(void);
int test_bytes_to_rr_3(void);
int test_bytes_to_rr_4(void);
int test_name_decompression_1(void);
int test_b64_encoding_1(void);
int test_b64_encoding_2(void);
int test_b64_encoding_3(void);
int test_b64_encoding_4(void);
int test_b64_encoding_5(void);
int test_b64_encoding_6(void);
int test_a_record_decoding_1(void);
int test_ns_record_decoding_1(void);
int test_cname_record_decoding_1(void);
int test_soa_record_decoding_1(void);
int test_ptr_record_decoding_1(void);
int test_hinfo_record_decoding_1(void);
int test_afsdb_record_decoding_1(void);
int test_txt_record_decoding_1(void);
int test_srv_record_decoding_1(void);
int test_naptr_record_decoding_1(void);
int test_cert_record_decoding_1(void);

void printf_encoded_name(char *encoded_name);
int cmp_u16array(uint16_t *array1, uint16_t *array2, int num_elements);
int cmparray(uint8_t *array1, uint8_t *array2, int num_elements);
void print_arrays(uint8_t *array1, uint8_t *array2, uint32_t num_elements);

int total_tests = 0;
int tests_failed = 0;

int main(int argc, char *argv[])
{
    FILE *devnull = fopen("/dev/null", "w");
    dup2(fileno(devnull), 2);

    //Test domain encoding function
    test_domain_encoding_1();
    test_domain_encoding_2();
    test_domain_encoding_3();
    test_domain_encoding_4();
    test_domain_encoding_5();
    test_domain_encoding_6();
    test_domain_encoding_7();
    test_domain_encoding_8();
    test_domain_encoding_9();
    test_domain_encoding_10();
    // Test domain decoding from wire format
    test_domain_decoding_1();
    test_domain_decoding_2();
    // Test header wire format
    test_header_generation_1();
    test_header_generation_2();
    test_header_generation_3();
    test_header_generation_4();
    // Test question wire format
    test_question_generation_1();
    test_question_generation_2();
    test_question_generation_3();
    test_question_generation_4();
    test_question_generation_5();
    // Test answer wire format
    test_answer_wire_uncompressed_1();
    test_answer_wire_uncompressed_2();
    test_answer_wire_uncompressed_3();
    test_answer_wire_uncompressed_4();
    // Test full query wire format
    test_query_wire_uncompressed_1();
    // Test array len function
    test_array_count_1();
    test_array_count_2();
    // Test Query Packet speed
    test_packet_generation_perf_1();
    // Test header bytes decoding
    test_bytes_to_header_1();
    test_bytes_to_header_2();
    // Test question bytes decoding
    test_bytes_to_question_1();
    test_bytes_to_question_2();
    // Test answer bytes decoding
    test_bytes_to_rr_1();
    test_bytes_to_rr_2();
    test_bytes_to_rr_3();
    test_bytes_to_rr_4();
    // Test name decompression
    test_name_decompression_1();
    // Test base 64 encoding
    test_b64_encoding_1();
    test_b64_encoding_2();
    test_b64_encoding_3();
    test_b64_encoding_4();
    test_b64_encoding_5();
    test_b64_encoding_6();
    // Test rdata decoding functions
    test_a_record_decoding_1();
    test_ns_record_decoding_1();
    test_cname_record_decoding_1();
    test_soa_record_decoding_1();
    test_ptr_record_decoding_1();
    test_hinfo_record_decoding_1();
    test_afsdb_record_decoding_1();
    test_txt_record_decoding_1();
    test_srv_record_decoding_1();
    test_naptr_record_decoding_1();
    test_cert_record_decoding_1();

    printf("Test results: %d / %d\n", total_tests - tests_failed, total_tests);
    return 0;
}

int test_domain_encoding_1()
{
    char name[] = "www.example.com.";
    char encoded_name[] = "3www7example3com0";
    encoded_name[0] = 3;
    encoded_name[4] = 7;
    encoded_name[12] = 3;
    encoded_name[16] = 0;
    _assert(strcmp(encoded_name, encode_domain_name(name)) == 0);
    return 0;
}

int test_domain_encoding_2()
{
    char name[] = "example.com.";
    char encoded_name[] = "7example3com0";
    encoded_name[0] = 7;
    encoded_name[8] = 3;
    encoded_name[12] = 0;
    _assert(strcmp(encoded_name, encode_domain_name(name)) == 0);
    return 0;
}

int test_domain_encoding_3()
{
    // Number incorrect
    char name[] = "example.com.";
    char encoded_name[] = "6example3com0";
    encoded_name[0] = 6;
    encoded_name[8] = 3;
    encoded_name[12] = 0;
    _assert(strcmp(encoded_name, encode_domain_name(name)) != 0);
    return 0;
}

int test_domain_encoding_4()
{
    // Edge case, root zone
    char name[] = ".";
    char encoded_name[] = "0";
    encoded_name[0] = 0;
    _assert(strcmp(encoded_name, encode_domain_name(name)) == 0);
    return 0;
}

int test_domain_encoding_5()
{
    char name[] = "a.b.c.d.";
    char encoded_name[] = "1a1b1c1d0";
    encoded_name[0] = 1;
    encoded_name[2] = 1;
    encoded_name[4] = 1;
    encoded_name[6] = 1;
    encoded_name[8] = 0;
    _assert(strcmp(encoded_name, encode_domain_name(name)) == 0);
    return 0;
}

int test_domain_encoding_6()
{
    // Test label length limit - this is an ok length (62)
    char name[] = "veryveryveryveryveryveryveryveryveryveryveryveryverylongdomain.com.";
    char encoded_name[] = "6veryveryveryveryveryveryveryveryveryveryveryveryverylongdomain3com0";
    encoded_name[0] = 62;
    encoded_name[63] = 3;
    encoded_name[67] = 0;
    _assert(strcmp(encoded_name, encode_domain_name(name)) == 0);
    return 0;
}

int test_domain_encoding_7()
{
    // Test label length limit - this is also an ok length (63)
    char name[] = "vveryveryveryveryveryveryveryveryveryveryveryveryverylongdomain.com.";
    char encoded_name[] = "6vveryveryveryveryveryveryveryveryveryveryveryveryverylongdomain3com0";
    encoded_name[0] = 63;
    encoded_name[64] = 3;
    encoded_name[68] = 0;
    _assert(strcmp(encoded_name, encode_domain_name(name)) == 0);
    return 0;
}

int test_domain_encoding_8()
{
    // Test label length limit - this NOT an ok length (64)
    char name[] = "veveryveryveryveryveryveryveryveryveryveryveryveryverylongdomain.com.";
    _assert(encode_domain_name(name) == NULL);
    return 0;
}

int test_domain_encoding_9()
{
    // Test name length limit - this is an ok length (255)
    char name[] = "veryveryveryveryveryveryveryveryveryveryveryveryveryveryve.yveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryve.yveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryve.yveryveryveryveryveryveryveryveryveryveryveryveryverylongdomain.com.";
    char encoded_name[] = ".veryveryveryveryveryveryveryveryveryveryveryveryveryveryve.yveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryve.yveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryve.yveryveryveryveryveryveryveryveryveryveryveryveryverylongdomain.com.";
    encoded_name[0] = 58;
    encoded_name[59] = 63;
    encoded_name[123] = 63;
    encoded_name[187] = 63;
    encoded_name[251] = 3;
    encoded_name[255] = 0;
    _assert(strcmp(encoded_name, encode_domain_name(name)) == 0);
    return 0;
}

int test_domain_encoding_10()
{
    // Test name length limit - this is not ok length (256)
    char name[] = "vveryveryveryveryveryveryveryveryveryveryveryveryveryveryve.yveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryve.yveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryve.yveryveryveryveryveryveryveryveryveryveryveryveryverylongdomain.com.";
    _assert(encode_domain_name(name) == NULL);
    return 0;
}

int test_domain_decoding_1()
{
    char name[] = "www.example.com.";
    unsigned char encoded_name[] = "3www7example3com0";
    encoded_name[0] = 3;
    encoded_name[4] = 7;
    encoded_name[12] = 3;
    encoded_name[16] = 0;
    _assert(strcmp(name, decode_domain_name(encoded_name)) == 0);
    return 0;
}

int test_domain_decoding_2()
{
    char name[] = ".";
    unsigned char encoded_name[] = "";
    _assert(strcmp(name, decode_domain_name(encoded_name)) == 0);
    return 0;
}

int test_header_generation_1()
{
    uint16_t test_header[] = {
        0xAAAA,
        0x0100,
        0x0001,
        0x0000,
        0x0000,
        0x0000,
    };
    // Query with ID 0xAAAA with one question, recursion desired
    Header *generated_header = __init__header(0xAAAA, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0);
    _assert(cmp_u16array(test_header, generated_header->to_wire(generated_header), 6) == 0);
    return 0;
}

int test_header_generation_2()
{
    uint16_t test_header[] = {
        0xAAAA,
        0x8180,
        0x0001,
        0x0001,
        0x0000,
        0x0000,
    };
    // Response with ID 0xAAAA with one question, one answer, recursion desired, recursion available
    Header *generated_header = __init__header(0xAAAA, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0);
    _assert(cmp_u16array(test_header, generated_header->to_wire(generated_header), 6) == 0);
    return 0;
}

int test_header_generation_3()
{
    uint16_t test_header[] = {
        0xED60,
        0x0120,
        0x0001,
        0x0000,
        0x0000,
        0x0001,
    };
    // Query with ID 0xED60 with one question, one additional, recursion desired, auth desired
    Header *generated_header = __init__header(0xED60, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1);
    _assert(cmp_u16array(test_header, generated_header->to_wire(generated_header), 6) == 0);
    return 0;
}

int test_header_generation_4()
{
    uint16_t test_header[] = {
        0xED60,
        0x81a0,
        0x0001,
        0x0001,
        0x0000,
        0x0001,
    };
    // Response with ID 0xED60 with one question, one additional, one answer, recursion desired, auth desired
    Header *generated_header = __init__header(0xED60, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1);
    _assert(cmp_u16array(test_header, generated_header->to_wire(generated_header), 6) == 0);
    return 0;
}

int test_question_generation_1()
{
    uint8_t test_q[] = {
        0x06, 0x66, 0x72, 0x61, 0x7A, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00, // frazao.ca.
        0x00, 0x01,                                                       // QTYPE 1 (A)
        0x00, 0x01                                                        // QCLASS 1 (IN)
    };
    // frazao.ca IN A
    Question *generated_question = __init__question("frazao.ca.", 1, 1);
    _assert((cmparray(test_q, generated_question->to_wire(generated_question), 15) == 0));
    return 0;
}

int test_question_generation_2()
{
    uint8_t test_q[] = {
        0x06, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00, // google.com.
        0x00, 0x01,                                                             // QTYPE 1 (A)
        0x00, 0x01                                                              // QCLASS 1 (IN)
    };
    // google.com. IN A
    Question *generated_question = __init__question("google.com.", 1, 1);
    _assert((cmparray(test_q, generated_question->to_wire(generated_question), 16) == 0));
    return 0;
}

int test_question_generation_3()
{
    uint8_t test_q[] = {
        0x06, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00, // google.com.
        0x00, 0x1c,                                                             // QTYPE 28 (AAAA)
        0x00, 0x01                                                              // QCLASS 1 (IN)
    };
    // google.com. IN AAAA
    Question *generated_question = __init__question("google.com.", 28, 1);
    _assert((cmparray(test_q, generated_question->to_wire(generated_question), 16) == 0));
    return 0;
}

int test_question_generation_4()
{
    uint8_t test_q[] = {
        0x06, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00, // google.com.
        0x01, 0x01,                                                             // QTYPE 257 (CAA)
        0x00, 0x01                                                              // QCLASS 1 (IN)
    };
    // google.com. IN CAA
    Question *generated_question = __init__question("google.com.", 257, 1);
    _assert((cmparray(test_q, generated_question->to_wire(generated_question), 16) == 0));
    return 0;
}

int test_question_generation_5()
{
    uint8_t test_q[] = {
        0x06, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00, // google.com.
        0x80, 0x01,                                                             // QTYPE 32769 (DLV)
        0x00, 0x01                                                              // QCLASS 1 (IN)
    };
    // google.com. IN CAA
    Question *generated_question = __init__question("google.com.", 32769, 1);
    _assert((cmparray(test_q, generated_question->to_wire(generated_question), 16) == 0));
    return 0;
}

int test_answer_wire_uncompressed_1()
{
    uint8_t test_a[] = {
        0x06, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00, // google.com.
        0x01, 0x01,                                                             // QTYPE 1 (A) -- INCORRECT!
        0x00, 0x01,                                                             // QCLASS 1 (IN)
        0x00, 0x00, 0x00, 0xb9,                                                 // TTL of 185 seconds
        0x00, 0x04,                                                             // rdata length
        0xac, 0xd9, 0x0a, 0x6e                                                  // 172.217.10.110
    };
    // google.com. 185 IN A 172.217.10.110
    uint8_t rdata[] = {0xac, 0xd9, 0x0a, 0x6e};
    Answer *generated_answer = __init__answer("google.com.", 1, 1, 185, 4, rdata);
    // This should fail
    _assert((cmparray(test_a, generated_answer->to_wire(generated_answer), 26) != 0));
    return 0;
}

int test_answer_wire_uncompressed_2()
{
    uint8_t test_a[] = {
        0x06, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00, // google.com.
        0x00, 0x01,                                                             // QTYPE 1 (A)
        0x00, 0x01,                                                             // QCLASS 1 (IN)
        0x00, 0x00, 0x00, 0xb9,                                                 // TTL of 185 seconds
        0x00, 0x04,                                                             // rdata length
        0xac, 0xd9, 0x0a, 0x6e                                                  // 172.217.10.110
    };
    // google.com. 185 IN A 172.217.10.110
    uint8_t rdata[] = {0xac, 0xd9, 0x0a, 0x6e};
    Answer *generated_answer = __init__answer("google.com.", 1, 1, 185, 4, rdata);
    _assert((cmparray(test_a, generated_answer->to_wire(generated_answer), 26) == 0));
    return 0;
}

int test_answer_wire_uncompressed_3()
{
    uint8_t test_a[] = {
        0x06, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00,                        // google.com.
        0x00, 0x1c,                                                                                    // QTYPE 28 (AAAA)
        0x00, 0x01,                                                                                    // QCLASS 1 (IN)
        0x00, 0x00, 0x01, 0x2c,                                                                        // TTL of 300 seconds
        0x00, 0x10,                                                                                    // rdata length
        0x20, 0x01, 0x48, 0x60, 0x48, 0x02, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a // 2607:f8b0:4006:804::200e
    };
    // google.com. 300 IN AAAA 2607:f8b0:4006:804::200e
    uint8_t rdata[] = {0x20, 0x01, 0x48, 0x60, 0x48, 0x02, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a};
    Answer *generated_answer = __init__answer("google.com.", 28, 1, 300, 16, rdata);
    _assert((cmparray(test_a, generated_answer->to_wire(generated_answer), 38) == 0));
    return 0;
}

int test_answer_wire_uncompressed_4()
{
    uint8_t test_a[] = {
        0x03, 0x63, 0x6f, 0x6d, 0x00,                                           // com.
        0x00, 0x02,                                                             // QTYPE 2 (NS)
        0x00, 0x01,                                                             // QCLASS 1 (IN)
        0x00, 0x02, 0xa3, 0x00,                                                 // TTL of 172800 seconds
        0x00, 0x14,                                                             // rdata length (20)
        0x01, 0x62, 0x0c, 0x67, 0x74, 0x6c, 0x64, 0x2d, 0x73, 0x65, 0x72, 0x76, // b.gtld-servers.net.
        0x65, 0x72, 0x73, 0x03, 0x6e, 0x65, 0x74, 0x00                          // b.gtld-servers.net.
    };
    // com. 172800 IN NS b.gtld-servers.net.
    uint8_t rdata[] = {0x01, 0x62, 0x0c, 0x67, 0x74, 0x6c, 0x64, 0x2d, 0x73, 0x65,
                       0x72, 0x76, 0x65, 0x72, 0x73, 0x03, 0x6e, 0x65, 0x74, 0x00};
    Answer *generated_answer = __init__answer("com.", 2, 1, 172800, 20, rdata);
    _assert((cmparray(test_a, generated_answer->to_wire(generated_answer), 35) == 0));
    return 0;
}

int test_query_wire_uncompressed_1()
{
    uint8_t test_q[] = {
        0xAA, 0xAA,                                                             // ID
        0x01, 0x20,                                                             // RD and AD flag
        0x00, 0x01,                                                             // One question
        0x00, 0x00,                                                             // 0 answers
        0x00, 0x00,                                                             // 0 authority
        0x00, 0x00,                                                             // 0 additional
        0x06, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00, // google.com.
        0x00, 0x01,                                                             // QTYPE 1 (A)
        0x00, 0x01                                                              // QCLASS 1 (IN)
    };
    DNSMessage *generated_message = make_query_message("google.com.", 1, 1);
    _assert((cmparray(test_q + 2, generated_message->to_wire_uncompressed(generated_message) + 2, generated_message->__len__uncomp - 2) == 0));
    return 0;
}

int test_array_count_1()
{
    uint8_t array[] = {6, 10, 11, 12, 13, 14, 15, 3, 10, 11, 12, 0}; // length of 12
    _assert(arraylen(array) == 12);
    return 0;
}

int test_array_count_2()
{
    uint8_t array[] = {0}; // length of 1
    _assert(arraylen(array) == 1);
    return 0;
}

int test_packet_generation_perf_1()
{
    /*
    Tests query packet generation rate. Fails if rate falls below a minimum value.
    */
    uint32_t num_packets = 30000;
    int MIN_RATE = 50000;
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    for (uint32_t i = 0; i < num_packets; i++)
    {
        DNSMessage *test_message = make_query_message(
            "example.com.", 1, 1);

        if (test_message == NULL)
        {
            fprintf(stderr, "Unable to generate message, exiting\n");
            break;
        }

        uint8_t *packet_bytes = test_message->to_wire_uncompressed(test_message);
        test_message->__del__(test_message);
        free(packet_bytes);
    }
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    double gen_rate = num_packets / cpu_time_used;

    _assert(gen_rate > MIN_RATE);
    return 0;
}

int test_bytes_to_header_1()
{
    uint8_t test_header[] = {
        0xAA, 0xBB,
        0x01, 0x20,
        0x00, 0x01,
        0x00, 0x01,
        0x00, 0x01,
        0x00, 0x01};
    // Query with ID 0xAAAA with one question, recursion desired
    Header *gen_head = bytes_to_header(test_header);
    uint8_t *wire_form = malloc(sizeof(uint8_t) * 12);
    uint8_t *ptr_start;
    ptr_start = wire_form;
    for (int i = 0; i < gen_head->__len__ / 2; i++)
    {
        *wire_form = gen_head->to_wire(gen_head)[i] >> 8;
        *(wire_form + 1) = gen_head->to_wire(gen_head)[i] & 0xFF;
        wire_form += 2;
    }
    _assert(cmparray(test_header, ptr_start, 12) == 0);
    return 0;
}

int test_bytes_to_header_2()
{
    uint8_t test_header[] = {
        0xAB, 0xBC,
        0x12, 0x34,
        0x45, 0x67,
        0x89, 0xAB,
        0xCD, 0xEF,
        0xBE, 0xEF};
    Header *gen_head = bytes_to_header(test_header);
    uint8_t *wire_form = malloc(sizeof(uint8_t) * 12);
    uint8_t *ptr_start;
    ptr_start = wire_form;
    for (int i = 0; i < gen_head->__len__ / 2; i++)
    {
        *wire_form = gen_head->to_wire(gen_head)[i] >> 8;
        *(wire_form + 1) = gen_head->to_wire(gen_head)[i] & 0xFF;
        wire_form += 2;
    }
    _assert(cmparray(test_header, ptr_start, 12) == 0);
    return 0;
}

int test_bytes_to_question_1()
{
    /*
    Converts wire format question to C object.
    */
    uint8_t test_q[] = {
        0xAA, 0xAA,                                                             // ID
        0x01, 0x20,                                                             // RD and AD flag
        0x00, 0x01,                                                             // One question
        0x00, 0x00,                                                             // 0 answers
        0x00, 0x00,                                                             // 0 authority
        0x00, 0x00,                                                             // 0 additional
        0x06, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00, // google.com.
        0x00, 0x01,                                                             // QTYPE 1 (A)
        0x00, 0x01                                                              // QCLASS 1 (IN)
    };
    uint32_t cur_loc = 12;
    Question *gen_q = bytes_to_question(test_q, &cur_loc);
    //print_arrays(&test_q[12], gen_q->to_wire(gen_q), 16);
    //printf("%d\n", cur_loc);
    _assert(cmparray(&test_q[12], gen_q->to_wire(gen_q), 16) == 0);
    return 0;
}

int test_bytes_to_question_2()
{
    /*
    Converts wire format question to C object.
    Tests ability to decode compressed names.
    */
    uint8_t test_q[] = {
        0xAA, 0xAA,                                                             // ID
        0x01, 0x20,                                                             // RD and AD flag
        0x00, 0x01,                                                             // One question
        0x00, 0x00,                                                             // 0 answers
        0x00, 0x00,                                                             // 0 authority
        0x00, 0x00,                                                             // 0 additional
        0x06, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00, // google.com.
        0x00, 0x01,                                                             // QTYPE 1 (A)
        0x00, 0x01,                                                             // QCLASS 1 (IN)
        0xc0, 0x0c,                                                             // google.com.
        0x00, 0x02,                                                             // QTYPE 2 (A)
        0x00, 0x01                                                              // QCLASS 1 (IN)
    };

    uint8_t expected_wire[] = {
        0x06, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00, // google.com.
        0x00, 0x02,                                                             // QTYPE 1 (NS)
        0x00, 0x01,                                                             // QCLASS 1 (IN)
    };
    uint32_t cur_loc = 28;
    Question *gen_q = bytes_to_question(test_q, &cur_loc);
    //print_arrays(expected_wire, gen_q->to_wire(gen_q), 16);
    //printf("%d\n", cur_loc);
    _assert(cmparray(expected_wire, gen_q->to_wire(gen_q), 16) == 0);
    return 0;
}

int test_bytes_to_rr_1()
{
    uint8_t packet[] = {
        // Header
        0xbb, 0x02, // ID
        0x81, 0xa0, // QR(1) response, RD, RA, AD
        0x00, 0x01, // 1 question
        0x00, 0x01, // 1 answer
        0x00, 0x00, // 0 NS
        0x00, 0x01, // 1 additional
        // Question 1
        0x06, 0x66, 0x72, 0x61, 0x7a, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00, // qname frazao.ca
        0x00, 0x01,                                                       // qtype 1 (A)
        0x00, 0x01,                                                       // qclass 1 (IN)
        // Answer 1
        0xc0, 0x0c,             // rname (pointer to position 12)
        0x00, 0x01,             // rtype 1 (A)
        0x00, 0x01,             // class 1 (IN)
        0x00, 0x00, 0x00, 0x1d, // TTL (29 seconds)
        0x00, 0x04,             // rdlen (4 bytes)
        0x36, 0xc5, 0xc7, 0xf6, // rdata 54.197.199.246
        // Additional 1 - OPT follows a slightly different mechanism
        0x00,                   // rname '.' (root)
        0x00, 0x29,             // rtype 41 (OPT)
        0x02, 0x00,             // class, requestor's UDP payload size
        0x00, 0x00, 0x00, 0x00, // ttl, extended RCODE and flags
        0x00, 0x00              // rdlen, length of all rdata
    };
    uint8_t expected[] = {
        0x06, 0x66, 0x72, 0x61, 0x7a, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00, // qname frazao.ca.
        0x00, 0x01,                                                       // rtype 1 (A)
        0x00, 0x01,                                                       // class 1 (IN)
        0x00, 0x00, 0x00, 0x1d,                                           // TTL (29 seconds)
        0x00, 0x04,                                                       // rdlen (4 bytes)
        0x36, 0xc5, 0xc7, 0xf6,                                           // rdata 54.197.199.246
    };

    uint32_t cur_loc = 27;
    Answer *gen_a = (Answer *)bytes_to_resource_record(packet, &cur_loc);
    //print_arrays(expected, gen_a->to_wire(gen_a), 25);
    //printf("%d\n", cur_loc);
    _assert(cmparray(expected, gen_a->to_wire(gen_a), 25) == 0);
    return 0;
}

int test_bytes_to_rr_2()
{
    uint8_t packet[] = {
        // Header
        0xbb, 0x02, // ID
        0x81, 0xa0, // QR(1) response, RD, RA, AD
        0x00, 0x01, // 1 question
        0x00, 0x01, // 1 answer
        0x00, 0x00, // 0 NS
        0x00, 0x01, // 1 additional
        // Question 1
        0x06, 0x66, 0x72, 0x61, 0x7a, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00, // qname frazao.ca
        0x00, 0x01,                                                       // qtype 1 (A)
        0x00, 0x01,                                                       // qclass 1 (IN)
        // Answer 1
        0x06, 0x66, 0x72, 0x61, 0x7a, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00, // qname frazao.ca
        0x00, 0x01,                                                       // rtype 1 (A)
        0x00, 0x01,                                                       // class 1 (IN)
        0x00, 0x00, 0x00, 0x1d,                                           // TTL (29 seconds)
        0x00, 0x04,                                                       // rdlen (4 bytes)
        0x36, 0xc5, 0xc7, 0xf6,                                           // rdata 54.197.199.246
        // Additional 1 - OPT follows a slightly different mechanism
        0x00,                   // rname '.' (root)
        0x00, 0x29,             // rtype 41 (OPT)
        0x02, 0x00,             // class, requestor's UDP payload size
        0x00, 0x00, 0x00, 0x00, // ttl, extended RCODE and flags
        0x00, 0x00              // rdlen, length of all rdata
    };
    uint8_t expected[] = {
        0x06, 0x66, 0x72, 0x61, 0x7a, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00, // qname frazao.ca
        0x00, 0x01,                                                       // rtype 1 (A)
        0x00, 0x01,                                                       // class 1 (IN)
        0x00, 0x00, 0x00, 0x1d,                                           // TTL (29 seconds)
        0x00, 0x04,                                                       // rdlen (4 bytes)
        0x36, 0xc5, 0xc7, 0xf6,                                           // rdata 54.197.199.246
    };

    uint32_t cur_loc = 27;
    Answer *gen_a = (Answer *)bytes_to_resource_record(packet, &cur_loc);
    //print_arrays(expected, gen_a->to_wire(gen_a), 25);
    //printf("%d\n", cur_loc);
    _assert(cmparray(expected, gen_a->to_wire(gen_a), 25) == 0);
    return 0;
}

int test_bytes_to_rr_3()
{
    uint8_t packet[] = {
        // Header
        0xbb, 0x02, // ID
        0x81, 0xa0, // QR(1) response, RD, RA, AD
        0x00, 0x01, // 1 question
        0x00, 0x01, // 1 answer
        0x00, 0x00, // 0 NS
        0x00, 0x01, // 1 additional
        // Question 1
        0x03, 0x77, 0x77, 0x77, 0x06, 0x66, 0x72, 0x61, 0x7a, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00, // qname www.frazao.ca
        0x00, 0x05,                                                                               // qtype 5 (CNAME)
        0x00, 0x01,                                                                               // qclass 1 (IN)
        // Answer 1
        0xc0, 0x10,             // pointer (16) to name frazao.ca
        0x00, 0x05,             // rtype 5 (CNAME)
        0x00, 0x01,             // class 1 (IN)
        0x00, 0x00, 0x00, 0x1d, // TTL (29 seconds)
        0x00, 0x04,             // rdlen (4 bytes)
        0x36, 0xc5, 0xc7, 0xf6, // rdata 54.197.199.246
        // Additional 1 - OPT follows a slightly different mechanism
        0x00,                   // rname '.' (root)
        0x00, 0x29,             // rtype 41 (OPT)
        0x02, 0x00,             // class, requestor's UDP payload size
        0x00, 0x00, 0x00, 0x00, // ttl, extended RCODE and flags
        0x00, 0x00              // rdlen, length of all rdata
    };
    uint8_t expected[] = {
        0x06, 0x66, 0x72, 0x61, 0x7a, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00, // qname frazao.ca
        0x00, 0x05,                                                       // rtype 5 (CNAME)
        0x00, 0x01,                                                       // class 1 (IN)
        0x00, 0x00, 0x00, 0x1d,                                           // TTL (29 seconds)
        0x00, 0x04,                                                       // rdlen (4 bytes)
        0x36, 0xc5, 0xc7, 0xf6,                                           // rdata 54.197.199.246
    };

    uint32_t cur_loc = 31;
    Answer *gen_a = (Answer *)bytes_to_resource_record(packet, &cur_loc);
    //print_arrays(expected, gen_a->to_wire(gen_a), 25);
    //printf("%d\n", cur_loc);
    _assert(cmparray(expected, gen_a->to_wire(gen_a), 25) == 0);
    return 0;
}

int test_bytes_to_rr_4()
{
    uint8_t packet[] = {
        // Header
        0xbb, 0x02, // ID
        0x81, 0xa0, // QR(1) response, RD, RA, AD
        0x00, 0x01, // 1 question
        0x00, 0x01, // 1 answer
        0x00, 0x00, // 0 NS
        0x00, 0x01, // 1 additional
        // Question 1
        0x03, 0x77, 0x77, 0x77, 0x06, 0x66, 0x72, 0x61, 0x7a, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00, // qname www.frazao.ca
        0x00, 0x05,                                                                               // qtype 5 (CNAME)
        0x00, 0x01,                                                                               // qclass 1 (IN)
        // Answer 1
        0x01, 0x61, 0xc0, 0x0c, // a + pointer (12) to name www.frazao.ca
        0x00, 0x05,             // rtype 5 (CNAME)
        0x00, 0x01,             // class 1 (IN)
        0x00, 0x00, 0x00, 0x1d, // TTL (29 seconds)
        0x00, 0x04,             // rdlen (4 bytes)
        0x36, 0xc5, 0xc7, 0xf6, // rdata 54.197.199.246
        // Additional 1 - OPT follows a slightly different mechanism
        0x00,                   // rname '.' (root)
        0x00, 0x29,             // rtype 41 (OPT)
        0x02, 0x00,             // class, requestor's UDP payload size
        0x00, 0x00, 0x00, 0x00, // ttl, extended RCODE and flags
        0x00, 0x00              // rdlen, length of all rdata
    };
    uint8_t expected[] = {
        0x01, 0x61, 0x03, 0x77, 0x77, 0x77, 0x06, 0x66, 0x72, 0x61, 0x7a, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00, // qname frazao.ca
        0x00, 0x05,                                                                                           // rtype 5 (CNAME)
        0x00, 0x01,                                                                                           // class 1 (IN)
        0x00, 0x00, 0x00, 0x1d,                                                                               // TTL (29 seconds)
        0x00, 0x04,                                                                                           // rdlen (4 bytes)
        0x36, 0xc5, 0xc7, 0xf6,                                                                               // rdata 54.197.199.246
    };

    uint32_t cur_loc = 31;
    Answer *gen_a = (Answer *)bytes_to_resource_record(packet, &cur_loc);
    //print_arrays(expected, gen_a->to_wire(gen_a), 31);
    //printf("%d\n", cur_loc);
    _assert(cmparray(expected, gen_a->to_wire(gen_a), 31) == 0);
    return 0;
}

int test_name_decompression_1()
{
    uint8_t packet[] = {
        // Header
        0xbb, 0x02, // ID
        0x81, 0xa0, // QR(1) response, RD, RA, AD
        0x00, 0x01, // 1 question
        0x00, 0x01, // 1 answer
        0x00, 0x00, // 0 NS
        0x00, 0x01, // 1 additional
        // Question 1
        0x03, 0x77, 0x77, 0x77, 0x06, 0x66, 0x72, 0x61, 0x7a, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00, // qname www.frazao.ca
        0x00, 0x05,                                                                               // qtype 5 (CNAME)
        0x00, 0x01,                                                                               // qclass 1 (IN)
        // Answer 1
        0x01, 0x61, 0xc0, 0x0c, // a + pointer (12) to name www.frazao.ca
        0x00, 0x05,             // rtype 5 (CNAME)
        0x00, 0x01,             // class 1 (IN)
        0x00, 0x00, 0x00, 0x1d, // TTL (29 seconds)
        0x00, 0x04,             // rdlen (4 bytes)
        0x36, 0xc5, 0xc7, 0xf6, // rdata 54.197.199.246
        // Additional 1 - OPT follows a slightly different mechanism
        0x00,                   // rname '.' (root)
        0x00, 0x29,             // rtype 41 (OPT)
        0x02, 0x00,             // class, requestor's UDP payload size
        0x00, 0x00, 0x00, 0x00, // ttl, extended RCODE and flags
        0x00, 0x00              // rdlen, length of all rdata
    };
    uint32_t cur_loc = 31;
    uint8_t *encoded_name = decompress_name(packet, &cur_loc);
    uint8_t expected[] = {
        0x01, 0x61, 0x03, 0x77, 0x77, 0x77, 0x06, 0x66, 0x72, 0x61, 0x7a, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00};
    _assert(cmparray(expected, encoded_name, 17) == 0);
    return 0;
}

int test_name_decompression_2()
{
    uint8_t packet[] = {
        // Header
        0xbb, 0x02, // ID
        0x81, 0xa0, // QR(1) response, RD, RA, AD
        0x00, 0x01, // 1 question
        0x00, 0x01, // 1 answer
        0x00, 0x00, // 0 NS
        0x00, 0x01, // 1 additional
        // Question 1
        0x03, 0x77, 0x77, 0x77, 0x06, 0x66, 0x72, 0x61, 0x7a, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00, // qname www.frazao.ca
        0x00, 0x05,                                                                               // qtype 5 (CNAME)
        0x00, 0x01,                                                                               // qclass 1 (IN)
        // Answer 1
        0x01, 0x61, 0xc0, 0x0c, // a + pointer (12) to name www.frazao.ca
        0x00, 0x05,             // rtype 5 (CNAME)
        0x00, 0x01,             // class 1 (IN)
        0x00, 0x00, 0x00, 0x1d, // TTL (29 seconds)
        0x00, 0x04,             // rdlen (4 bytes)
        0x36, 0xc5, 0xc7, 0xf6, // rdata 54.197.199.246
        // Additional 1 - OPT follows a slightly different mechanism
        0x00,                   // rname '.' (root)
        0x00, 0x29,             // rtype 41 (OPT)
        0x02, 0x00,             // class, requestor's UDP payload size
        0x00, 0x00, 0x00, 0x00, // ttl, extended RCODE and flags
        0x00, 0x00              // rdlen, length of all rdata
    };
    uint32_t cur_loc = 31;
    uint8_t *encoded_name = decompress_name(packet, &cur_loc);
    uint8_t expected[] = {
        0x01, 0x61, 0x03, 0x77, 0x77, 0x77, 0x06, 0x66, 0x72, 0x61, 0x7a, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00};
    _assert(cmparray(expected, encoded_name, 17) == 0);
    return 0;
}

int test_b64_encoding_1()
{
    char decoded_text[] = "Man is distinguished, not only by his reason, but by this singular passion from other animals, "
                          "which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable "
                          "generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
    char encoded_text[] = "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlz"
                          "IHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2Yg"
                          "dGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGlu"
                          "dWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRo"
                          "ZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=";
    char *actual = base64_encode((uint8_t *)decoded_text, strlen(decoded_text));
    //printf("\n\n%s\n\n", encoded_text);
    //printf("\n\n%s\n\n", actual);
    _assert(strcmp(encoded_text, actual) == 0);
    return 0;
}

int test_b64_encoding_2()
{
    char decoded_text[] = "any carnal pleasure.";
    char encoded_text[] = "YW55IGNhcm5hbCBwbGVhc3VyZS4=";
    char *actual = base64_encode((uint8_t *)decoded_text, strlen(decoded_text));
    _assert(strcmp(encoded_text, actual) == 0);
    return 0;
}

int test_b64_encoding_3()
{
    char decoded_text[] = "any carnal pleasure";
    char encoded_text[] = "YW55IGNhcm5hbCBwbGVhc3VyZQ==";
    char *actual = base64_encode((uint8_t *)decoded_text, strlen(decoded_text));
    _assert(strcmp(encoded_text, actual) == 0);
    return 0;
}

int test_b64_encoding_4()
{
    char decoded_text[] = "any carnal pleasur";
    char encoded_text[] = "YW55IGNhcm5hbCBwbGVhc3Vy";
    char *actual = base64_encode((uint8_t *)decoded_text, strlen(decoded_text));
    _assert(strcmp(encoded_text, actual) == 0);
    return 0;
}

int test_b64_encoding_5()
{
    char decoded_text[] = "any carnal pleasu";
    char encoded_text[] = "YW55IGNhcm5hbCBwbGVhc3U=";
    char *actual = base64_encode((uint8_t *)decoded_text, strlen(decoded_text));
    _assert(strcmp(encoded_text, actual) == 0);
    return 0;
}

int test_b64_encoding_6()
{
    char decoded_text[] = "any carnal pleas";
    char encoded_text[] = "YW55IGNhcm5hbCBwbGVhcw==";
    char *actual = base64_encode((uint8_t *)decoded_text, strlen(decoded_text));
    _assert(strcmp(encoded_text, actual) == 0);
    return 0;
}

int test_a_record_decoding_1()
{
    uint8_t packet[] = {
        // Header
        0xbb, 0x02, // ID
        0x81, 0xa0, // QR(1) response, RD, RA, AD
        0x00, 0x01, // 1 question
        0x00, 0x01, // 1 answer
        0x00, 0x00, // 0 NS
        0x00, 0x01, // 1 additional
        // Question 1
        0x06, 0x66, 0x72, 0x61, 0x7a, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00, // qname frazao.ca
        0x00, 0x01,                                                       // qtype 1 (A)
        0x00, 0x01,                                                       // qclass 1 (IN)
        // Answer 1
        0x06, 0x66, 0x72, 0x61, 0x7a, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00, // qname frazao.ca
        0x00, 0x01,                                                       // rtype 1 (A)
        0x00, 0x01,                                                       // class 1 (IN)
        0x00, 0x00, 0x00, 0x1d,                                           // TTL (29 seconds)
        0x00, 0x04,                                                       // rdlen (4 bytes)
        0x36, 0xc5, 0xc7, 0xf6,                                           // rdata 54.197.199.246
        // Additional 1 - OPT follows a slightly different mechanism
        0x00,                   // rname '.' (root)
        0x00, 0x29,             // rtype 41 (OPT)
        0x02, 0x00,             // class, requestor's UDP payload size
        0x00, 0x00, 0x00, 0x00, // ttl, extended RCODE and flags
        0x00, 0x00              // rdlen, length of all rdata
    };

    DNSMessage *msg = packet_to_message(packet);
    char *decoded_answer = msg->ans[0]->rdata_to_str(msg->ans[0], packet);
    _assert(strcmp("54.197.199.246", decoded_answer) == 0);
    return 0;
}

int test_ns_record_decoding_1()
{
    uint8_t packet[] = {
        // Header
        0x35, 0xd4, // ID
        0x81, 0xa0, // QR(1) response, RD, RA, AD
        0x00, 0x01, // 1 question
        0x00, 0x04, // 4 answer
        0x00, 0x00, // 0 NS
        0x00, 0x01, // 1 additional
        // Question 1
        0x06, 0x66, 0x72, 0x61, 0x7a, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00, // qname frazao.ca
        0x00, 0x02,                                                       // qtype 2 (NS)
        0x00, 0x01,                                                       // qclass 1 (IN)
        // Answer 1
        0xc0, 0x0c,                                                                                                             // qname frazao.ca
        0x00, 0x02,                                                                                                             // rtype 2 (NS)
        0x00, 0x01,                                                                                                             // class 1 (IN)
        0x00, 0x00, 0x0e, 0x0f,                                                                                                 // TTL (3599 seconds)
        0x00, 0x14,                                                                                                             // rdlen (20 bytes)
        0x04, 0x64, 0x6e, 0x73, 0x31, 0x03, 0x70, 0x31, 0x30, 0x05, 0x6e, 0x73, 0x6f, 0x6e, 0x65, 0x03, 0x6e, 0x65, 0x74, 0x00, // rdata dns1.p10.nsone.net.
        // Answer 2
        0xc0, 0x0c,                               // qname frazao.ca
        0x00, 0x02,                               // rtype 2 (NS)
        0x00, 0x01,                               // class 1 (IN)
        0x00, 0x00, 0x0e, 0x0f,                   // TTL (3599 seconds)
        0x00, 0x07,                               // rdlen (7 bytes)
        0x04, 0x64, 0x6e, 0x73, 0x32, 0xc0, 0x2c, // rdata dns2.p10.nsone.net.
        // Answer 3
        0xc0, 0x0c,                               // qname frazao.ca
        0x00, 0x02,                               // rtype 2 (NS)
        0x00, 0x01,                               // class 1 (IN)
        0x00, 0x00, 0x0e, 0x0f,                   // TTL (3599 seconds)
        0x00, 0x07,                               // rdlen (7 bytes)
        0x04, 0x64, 0x6e, 0x73, 0x33, 0xc0, 0x2c, // rdata dns3.p10.nsone.net.
        // Answer 4
        0xc0, 0x0c,                               // qname frazao.ca
        0x00, 0x02,                               // rtype 2 (NS)
        0x00, 0x01,                               // class 1 (IN)
        0x00, 0x00, 0x0e, 0x0f,                   // TTL (3599 seconds)
        0x00, 0x07,                               // rdlen (7 bytes)
        0x04, 0x64, 0x6e, 0x73, 0x34, 0xc0, 0x2c, // rdata dns4.p10.nsone.net.
        // Additional 1 - OPT follows a slightly different mechanism
        0x00,                   // rname '.' (root)
        0x00, 0x29,             // rtype 41 (OPT)
        0x02, 0x00,             // class, requestor's UDP payload size
        0x00, 0x00, 0x00, 0x00, // ttl, extended RCODE and flags
        0x00, 0x00              // rdlen, length of all rdata
    };

    DNSMessage *msg = packet_to_message(packet);
    char *decoded_answer;
    char *expected[4] = {
        "dns1.p10.nsone.net.",
        "dns2.p10.nsone.net.",
        "dns3.p10.nsone.net.",
        "dns4.p10.nsone.net."};
    for (int i = 0; i < 4; i++)
    {
        decoded_answer = msg->ans[i]->rdata_to_str(msg->ans[i], packet);
        _assert(strcmp(expected[i], decoded_answer) == 0);
    }
    return 0;
}

int test_cname_record_decoding_1()
{
    uint8_t packet[] = {
        // Header
        0x5d, 0x03, // ID
        0x81, 0xa0, // QR(1) response, RD, RA, AD
        0x00, 0x01, // 1 question
        0x00, 0x02, // 2 answer
        0x00, 0x01, // 1 NS
        0x00, 0x01, // 1 additional
        // Question 1
        0x05, 0x63, 0x6e, 0x61, 0x6d, 0x65, 0x06, 0x66, 0x72, 0x61, 0x7a, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00, // qname cname.frazao.ca
        0x00, 0x01,                                                                                           // rtype 1 (A)
        0x00, 0x01,                                                                                           // Class 1 (IN)
        // Answer 1
        0xc0, 0x0c,                                                       // qname ptr
        0x00, 0x05,                                                       // rtype 5 (CNAME)
        0x00, 0x01,                                                       // Class 1 (IN)
        0x00, 0x00, 0x00, 0x10,                                           // TTL 16
        0x00, 0x0b,                                                       // rdata len 11
        0x08, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x65, 0x64, 0xc0, 0x12, // cname weighted.<ptr to qname>
        // Answer 2
        0xc0, 0x2d,                   // qname ptr to answer 1
        0x00, 0x05,                   // rtype 5 (CNAME)
        0x00, 0x01,                   // Class 1 (IN)
        0x00, 0x00, 0x00, 0x1d,       // TTL 29
        0x00, 0x05,                   // rdata len 5
        0x03, 0x6f, 0x6e, 0x65, 0x00, // cname "one"
        // Authority 1
        0xc0, 0x44,                                                                                                                                           // qname ("one")
        0x00, 0x06,                                                                                                                                           // rtype 6 SOA
        0x00, 0x01,                                                                                                                                           // Class 1
        0x00, 0x00, 0x03, 0x83,                                                                                                                               // TTL 899
        0x00, 0x35,                                                                                                                                           // rdata len 53
        0x01, 0x61, 0x03, 0x6e, 0x69, 0x63, 0xc0, 0x44,                                                                                                       // mname a.nic.one.
        0x07, 0x73, 0x75, 0x70, 0x70, 0x6f, 0x72, 0x74, 0x0b, 0x61, 0x72, 0x69, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x73, 0x03, 0x63, 0x6f, 0x6d, 0x00, // rname support.ariservices.com.
        0x5c, 0xfa, 0xb0, 0xa5,                                                                                                                               // Serial
        0x00, 0x00, 0x07, 0x08,                                                                                                                               // Refresh
        0x00, 0x00, 0x01, 0x2c,                                                                                                                               // Retry
        0x00, 0x1b, 0xaf, 0x80,                                                                                                                               // Expire
        0x00, 0x00, 0x07, 0x08,                                                                                                                               // Minimum
        // Additional 1 - OPT follows a slightly different mechanism
        0x00,                   // rname '.' (root)
        0x00, 0x29,             // rtype 41 (OPT)
        0x02, 0x00,             // class, requestor's UDP payload size (512 bytes)
        0x00, 0x00, 0x00, 0x00, // ttl, extended RCODE and flags
        0x00, 0x00              // rdlen, length of all rdata
    };

    DNSMessage *msg = packet_to_message(packet);
    int num_answers = 2;
    char *decoded_answer;
    char *expected[] = {
        "weighted.frazao.ca.",
        "one."};
    for (int i = 0; i < num_answers; i++)
    {
        decoded_answer = msg->ans[i]->rdata_to_str(msg->ans[i], packet);
        _assert(strcmp(expected[i], decoded_answer) == 0);
    }
    return 0;
}

int test_soa_record_decoding_1()
{
    uint8_t packet[] = {
        // Header
        0x5d, 0x03, // ID
        0x81, 0xa0, // QR(1) response, RD, RA, AD
        0x00, 0x01, // 1 question
        0x00, 0x02, // 2 answer
        0x00, 0x01, // 1 NS
        0x00, 0x01, // 1 additional
        // Question 1
        0x05, 0x63, 0x6e, 0x61, 0x6d, 0x65, 0x06, 0x66, 0x72, 0x61, 0x7a, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00, // qname cname.frazao.ca
        0x00, 0x01,                                                                                           // rtype 1 (A)
        0x00, 0x01,                                                                                           // Class 1 (IN)
        // Answer 1
        0xc0, 0x0c,                                                       // qname ptr
        0x00, 0x05,                                                       // rtype 5 (CNAME)
        0x00, 0x01,                                                       // Class 1 (IN)
        0x00, 0x00, 0x00, 0x10,                                           // TTL 16
        0x00, 0x0b,                                                       // rdata len 11
        0x08, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x65, 0x64, 0xc0, 0x12, // cname weighted.<ptr to qname>
        // Answer 2
        0xc0, 0x2d,                   // qname ptr to answer 1
        0x00, 0x05,                   // rtype 5 (CNAME)
        0x00, 0x01,                   // Class 1 (IN)
        0x00, 0x00, 0x00, 0x1d,       // TTL 29
        0x00, 0x05,                   // rdata len 5
        0x03, 0x6f, 0x6e, 0x65, 0x00, // cname "one"
        // Authority 1
        0xc0, 0x44,                                                                                                                                           // qname ("one")
        0x00, 0x06,                                                                                                                                           // rtype 6 SOA
        0x00, 0x01,                                                                                                                                           // Class 1
        0x00, 0x00, 0x03, 0x83,                                                                                                                               // TTL 899
        0x00, 0x35,                                                                                                                                           // rdata len 53
        0x01, 0x61, 0x03, 0x6e, 0x69, 0x63, 0xc0, 0x44,                                                                                                       // mname a.nic.one.
        0x07, 0x73, 0x75, 0x70, 0x70, 0x6f, 0x72, 0x74, 0x0b, 0x61, 0x72, 0x69, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x73, 0x03, 0x63, 0x6f, 0x6d, 0x00, // rname support.ariservices.com.
        0x5c, 0xfa, 0xb0, 0xa5,                                                                                                                               // Serial
        0x00, 0x00, 0x07, 0x08,                                                                                                                               // Refresh
        0x00, 0x00, 0x01, 0x2c,                                                                                                                               // Retry
        0x00, 0x1b, 0xaf, 0x80,                                                                                                                               // Expire
        0x00, 0x00, 0x07, 0x08,                                                                                                                               // Minimum
        // Additional 1 - OPT follows a slightly different mechanism
        0x00,                   // rname '.' (root)
        0x00, 0x29,             // rtype 41 (OPT)
        0x02, 0x00,             // class, requestor's UDP payload size (512 bytes)
        0x00, 0x00, 0x00, 0x00, // ttl, extended RCODE and flags
        0x00, 0x00              // rdlen, length of all rdata
    };

    DNSMessage *msg = packet_to_message(packet);
    char *decoded_answer;
    char expected[] = "a.nic.one. support.ariservices.com. 1559933093 1800 300 1814400 1800";
    decoded_answer = msg->auth[0]->rdata_to_str(msg->auth[0], packet);
    _assert(strcmp(expected, decoded_answer) == 0);
    return 0;
}

int test_ptr_record_decoding_1()
{
    uint8_t packet[] = {
        // Header
        0x95, 0x2b, // ID
        0x81, 0x80, // QR(1) response, RD, RA
        0x00, 0x01, // 1 question
        0x00, 0x01, // 1 answer
        0x00, 0x00, // 0 NS
        0x00, 0x01, // 1 additional
        // Question 1
        0x02, 0x34, 0x36, 0x02, 0x31, 0x31, 0x03, 0x32, 0x31, 0x37, 0x03, 0x31, 0x37, 0x32, 0x07, 0x69, 0x6e, 0x2d, 0x61, 0x64, 0x64, 0x72, 0x04, 0x61, 0x72, 0x70, 0x61, 0x00,
        0x00, 0x0c, // Rtype 12 (PTR)
        0x00, 0x01, // Class 1 (IN)
        // Answer 1
        0xc0, 0x0c,             // qname ptr
        0x00, 0x0c,             // Rtype 12 (PTR)
        0x00, 0x01,             // Class 1 (IN)
        0x00, 0x00, 0x10, 0xb7, // TTL 4279
        0x00, 0x1b,             // rdata len 27
        0x0f, 0x6c, 0x67, 0x61, 0x32, 0x35, 0x73, 0x36, 0x31, 0x2d, 0x69, 0x6e, 0x2d, 0x66, 0x31, 0x34, 0x05, 0x31, 0x65, 0x31, 0x30, 0x30, 0x03, 0x6e, 0x65, 0x74, 0x00,
        // Additional
        0x00,
        0x00, 0x29,
        0x0f, 0xa0,             // UDP packet size 4000
        0x00, 0x00, 0x00, 0x00, // ttl, extended RCODE and flags
        0x00, 0x00              // rdlen, length of all rdata
    };

    DNSMessage *msg = packet_to_message(packet);
    char *decoded_answer;
    char expected[] = "lga25s61-in-f14.1e100.net.";
    decoded_answer = msg->ans[0]->rdata_to_str(msg->ans[0], packet);
    _assert(strcmp(expected, decoded_answer) == 0);
    return 0;
}

int test_hinfo_record_decoding_1()
{
    uint8_t packet[] = {
        // Header
        0xec, 0x9e, // ID
        0x81, 0x80, // QR(1) response, RD, RA
        0x00, 0x01, // 1 question
        0x00, 0x01, // 1 answer
        0x00, 0x00, // 0 NS
        0x00, 0x01, // 1 additional
        // Question
        0x0c, 0x7a, 0x6f, 0x6e, 0x65, 0x74, 0x72, 0x61, 0x6e, 0x73, 0x66, 0x65, 0x72, 0x02, 0x6d, 0x65, 0x00, // qname zonetransfer.me
        0x00, 0x0d,                                                                                           // rtype 13 (HINFO)
        0x00, 0x01,                                                                                           // Class 1 (IN)
        // Answer 1
        0xc0, 0x0c,                                                                   // qname ptr
        0x00, 0x0d,                                                                   // rtype 13 (HINFO)
        0x00, 0x01,                                                                   // Class 1 (IN)
        0x00, 0x00, 0x01, 0x2c,                                                       // TTL 300
        0x00, 0x19,                                                                   // rdata len 25
        0x0d,                                                                         // CPU len 13
        0x43, 0x61, 0x73, 0x69, 0x6f, 0x20, 0x66, 0x78, 0x2d, 0x37, 0x30, 0x30, 0x47, // Casio fx-700g
        0x0a,                                                                         // OS len 10
        0x57, 0x69, 0x6e, 0x64, 0x6f, 0x77, 0x73, 0x20, 0x58, 0x50,                   // Windows XP
        // Additional
        0x00,
        0x00, 0x29,
        0x0f, 0xa0,             // UDP packet size 4000
        0x00, 0x00, 0x00, 0x00, // ttl, extended RCODE and flags
        0x00, 0x00              // rdlen, length of all rdata
    };

    DNSMessage *msg = packet_to_message(packet);
    char *decoded_answer;
    char expected[] = "Casio fx-700G Windows XP";
    decoded_answer = msg->ans[0]->rdata_to_str(msg->ans[0], packet);
    _assert(strcmp(expected, decoded_answer) == 0);
    return 0;
}

int test_afsdb_record_decoding_1()
{
    uint8_t packet[] = {
        // Header
        0xd2, 0xa4, // ID
        0x85, 0x00, // QR(1) response, RD, AA
        0x00, 0x01, // 1 question
        0x00, 0x01, // 1 answer
        0x00, 0x00, // 0 NS
        0x00, 0x01, // 1 additional
        // Question
        0x05, 0x61, 0x66, 0x73, 0x64, 0x62, 0x06, 0x66, 0x72, 0x61, 0x7a, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00, // afsdb.frazao.ca.
        0x00, 0x12,                                                                                           // rtype 12 (afsdb)
        0x00, 0x01,                                                                                           // class 1 (IN)
        // Answer
        0xc0, 0x0c,                                                                                                                   // qname ptr
        0x00, 0x12,                                                                                                                   // rtype 12 (afsdb)
        0x00, 0x01,                                                                                                                   // class 1 (IN)
        0x00, 0x00, 0x00, 0x1e,                                                                                                       // TTL 30
        0x00, 0x17,                                                                                                                   // rdata len 23
        0x00, 0x01,                                                                                                                   // subtype 1
        0x07, 0x62, 0x69, 0x67, 0x62, 0x69, 0x72, 0x64, 0x07, 0x74, 0x6f, 0x61, 0x73, 0x74, 0x65, 0x72, 0x03, 0x63, 0x6f, 0x6d, 0x00, // bigbird.toaster.com.
        // Additional
        0x00,
        0x00, 0x29,
        0x0f, 0xa0,             // UDP packet size 4000
        0x00, 0x00, 0x00, 0x00, // ttl, extended RCODE and flags
        0x00, 0x00              // rdlen, length of all rdata
    };

    DNSMessage *msg = packet_to_message(packet);
    char *decoded_answer;
    char expected[] = "1 bigbird.toaster.com.";
    decoded_answer = msg->ans[0]->rdata_to_str(msg->ans[0], packet);
    _assert(strcmp(expected, decoded_answer) == 0);
    return 0;
}

int test_txt_record_decoding_1()
{
    uint8_t packet[] = {
        // Header
        0xd2, 0xa4, // ID
        0x85, 0x00, // QR(1) response, RD, AA
        0x00, 0x01, // 1 question
        0x00, 0x01, // 1 answer
        0x00, 0x00, // 0 NS
        0x00, 0x00, // 0 additional
        // Question
        0x07, 0x6c, 0x6f, 0x6e, 0x67, 0x74, 0x78, 0x74, 0x06, 0x66, 0x72, 0x61, 0x7a, 0x61, 0x6f, 0x02, 0x63, 0x61, 0x00, // qname longtxt.frazao.ca.
        0x00, 0x10,                                                                                                       // rtype 16 (txt)
        0x00, 0x01,                                                                                                       // class 1 (IN)
        // Answer
        0xc0, 0x0c,             // qname ptr
        0x00, 0x10,             // rtype 16 (txt)
        0x00, 0x01,             // Class 1 (IN)
        0x00, 0x00, 0x00, 0x1e, // TTL 30
        0x03, 0x71,             // rdata len 881
        0xff,                   // txt len (255)
        0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x20, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c,
        0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48,
        0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57,
        0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c,
        0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72,
        0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f,
        0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64,
        0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20,
        0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65,
        0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f,
        0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c,
        0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c,
        0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c,
        0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65,
        0xff, // txt len (255)
        0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f,
        0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c,
        0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c,
        0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c,
        0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48,
        0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57,
        0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c,
        0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72,
        0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f,
        0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64,
        0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20,
        0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65,
        0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f,
        0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f,
        0xff, // txt len (255)
        0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64,
        0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20,
        0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65,
        0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f,
        0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c,
        0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c,
        0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c,
        0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48,
        0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57,
        0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c,
        0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72,
        0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f,
        0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64,
        0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57,
        0x70, // txt len (112)
        0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c,
        0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72,
        0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f,
        0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64,
        0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20,
        0x57, 0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64};

    DNSMessage *msg = packet_to_message(packet);
    char *decoded_answer;
    char expected[] = "\"Hello, World Hello, WorldHello, WorldHello, WorldHello, WorldHello, WorldHello, WorldHello, "
                      "WorldHello, WorldHello, WorldHello, WorldHello, WorldHello, WorldHello, WorldHello, WorldHello,"
                      " WorldHello, WorldHello, WorldHello, WorldHello, WorldHello, WorldHe\" \"llo, WorldHello, World"
                      "Hello, WorldHello, WorldHello, WorldHello, WorldHello, WorldHello, WorldHello, WorldHello, Worl"
                      "dHello, WorldHello, WorldHello, WorldHello, WorldHello, WorldHello, WorldHello, WorldHello, Wor"
                      "ldHello, WorldHello, WorldHello, WorldHello\" \", WorldHello, WorldHello, WorldHello, WorldHell"
                      "o, WorldHello, WorldHello, WorldHello, WorldHello, WorldHello, WorldHello, WorldHello, WorldHel"
                      "lo, WorldHello, WorldHello, WorldHello, WorldHello, WorldHello, WorldHello, WorldHello, WorldHe"
                      "llo, WorldHello, W\" \"orldHello, WorldHello, WorldHello, WorldHello, WorldHello, WorldHello, W"
                      "orldHello, WorldHello, WorldHello, World\"";
    decoded_answer = msg->ans[0]->rdata_to_str(msg->ans[0], packet);
    _assert(strcmp(expected, decoded_answer) == 0);
    return 0;
}

int test_srv_record_decoding_1()
{
    uint8_t packet[] = {
        // Header
        0x27, 0x00, // ID
        0x85, 0x00, // QR(1) response, RD, AA
        0x00, 0x01, // 1 question
        0x00, 0x01, // 1 answer
        0x00, 0x00, // 0 NS
        0x00, 0x01, // 1 additional
        // Question
        0x04, 0x5f, 0x73, 0x69, 0x70, 0x04, 0x5f, 0x74, 0x63, 0x70, 0x08, 0x63, 0x68, 0x75, 0x6e, 0x64, 0x65,       // qname
        0x72, 0x6d, 0x03, 0x64, 0x65, 0x76, 0x06, 0x74, 0x77, 0x69, 0x6c, 0x69, 0x6f, 0x03, 0x63, 0x6f, 0x6d, 0x00, // qname
        0x00, 0x21,                                                                                                 // rtype 33 (srv)
        0x00, 0x01,                                                                                                 // class 1 (IN)
        // Answer
        0xc0, 0x0c,                                                                                                 // qname ptr
        0x00, 0x21,                                                                                                 // rtype 33 (srv)
        0x00, 0x01,                                                                                                 // class 1 (IN)
        0x00, 0x00, 0x00, 0x3c,                                                                                     // TTL 60
        0x00, 0x2a,                                                                                                 // rdata len 42
        0x00, 0x0a,                                                                                                 // priority 10
        0x00, 0x64,                                                                                                 // weight 100
        0x27, 0xd1,                                                                                                 // port 10193
        0x08, 0x63, 0x68, 0x75, 0x6e, 0x64, 0x65, 0x72, 0x6d, 0x06, 0x6c, 0x65, 0x67, 0x61, 0x63, 0x79, 0x03, 0x67, // target
        0x6c, 0x6c, 0x03, 0x64, 0x65, 0x76, 0x06, 0x74, 0x77, 0x69, 0x6c, 0x69, 0x6f, 0x03, 0x63, 0x6f, 0x6d, 0x00, // target
        // Additional
        0x00,
        0x00, 0x29,
        0x0f, 0xa0,             // UDP packet size 4000
        0x00, 0x00, 0x00, 0x00, // ttl, extended RCODE and flags
        0x00, 0x00              // rdlen, length of all rdata
    };

    DNSMessage *msg = packet_to_message(packet);
    char *decoded_answer;
    char expected[] = "10 100 10193 chunderm.legacy.gll.dev.twilio.com.";
    decoded_answer = msg->ans[0]->rdata_to_str(msg->ans[0], packet);
    _assert(strcmp(expected, decoded_answer) == 0);
    return 0;
}

int test_naptr_record_decoding_1()
{
    uint8_t packet[] = {
        // Header
        0x1d, 0x8c, // ID
        0x85, 0x00, // QR(1) response, RD, AA
        0x00, 0x01, // 1 question
        0x00, 0x03, // 3 answers
        0x00, 0x00, // 0 NS
        0x00, 0x01, // 1 Additional
        // Question
        0x03, 0x73, 0x69, 0x70,                                                             // sip.
        0x0d, 0x73, 0x74, 0x61, 0x67, 0x65, 0x2d, 0x75, 0x73, 0x32, 0x2d, 0x74, 0x6e, 0x78, // stage-us2-tnx.
        0x06, 0x74, 0x77, 0x69, 0x6c, 0x69, 0x6f,                                           // twilio.
        0x03, 0x63, 0x6f, 0x6d, 0x00,                                                       // com.
        0x00, 0x23,                                                                         // rtype 35 (naptr)
        0x00, 0x01,                                                                         // class 1 (IN)
        // Answer 1
        0xc0, 0x0c,                               // qname ptr
        0x00, 0x23,                               // rtype 35 (naptr)
        0x00, 0x01,                               // class 1 (IN)
        0x00, 0x00, 0x07, 0x08,                   // TTL 1800
        0x00, 0x37,                               // rdata len 55
        0x00, 0x0a,                               // order 10
        0x00, 0x0a,                               // preference 10
        0x01,                                     // flags len 1
        0x53,                                     // service flags S
        0x07,                                     // service len 7
        0x53, 0x49, 0x50, 0x2b, 0x44, 0x32, 0x55, // service: SIP+D2U
        0x00,                                     // regex len 0
        0x04, 0x5f, 0x73, 0x69, 0x70, 0x04, 0x5f, 0x75, 0x64, 0x70, 0x03, 0x73, 0x69,
        0x70, 0x0d, 0x73, 0x74, 0x61, 0x67, 0x65, 0x2d, 0x75, 0x73, 0x32, 0x2d, 0x74,
        0x6e, 0x78, 0x06, 0x74, 0x77, 0x69, 0x6c, 0x69, 0x6f, 0x03, 0x63, 0x6f, 0x6d,
        0x00, // replacement: _sip._udp.sip.stage-us2-tnx.twilio.com
        // Answer 2
        0xc0, 0x0c,                               // qname ptr
        0x00, 0x23,                               // rtype 35 (naptr)
        0x00, 0x01,                               // class 1 (IN)
        0x00, 0x00, 0x07, 0x08,                   // TTL 1800
        0x00, 0x37,                               // rdata len 55
        0x00, 0x14,                               // order 20
        0x00, 0x0a,                               // preference 10
        0x01,                                     // flag len 1
        0x53,                                     // flag S
        0x07,                                     // service len 7
        0x53, 0x49, 0x50, 0x2b, 0x44, 0x32, 0x54, // SIP+D2T
        0x00,                                     // regex len 0
        0x04, 0x5f, 0x73, 0x69, 0x70, 0x04, 0x5f, 0x74, 0x63, 0x70, 0x03, 0x73, 0x69,
        0x70, 0x0d, 0x73, 0x74, 0x61, 0x67, 0x65, 0x2d, 0x75, 0x73, 0x32, 0x2d, 0x74,
        0x6e, 0x78, 0x06, 0x74, 0x77, 0x69, 0x6c, 0x69, 0x6f, 0x03, 0x63, 0x6f, 0x6d,
        0x00, // replacement: _sip._tcp.sip.stage-us2-tnx.twilio.com
        // Answer 3
        0xc0, 0x0c,                                     // qname ptr
        0x00, 0x23,                                     // rtype 35 (naptr)
        0x00, 0x01,                                     // class 1 (IN)
        0x00, 0x00, 0x07, 0x08,                         // TTL 1800
        0x00, 0x39,                                     // len 57
        0x00, 0x1e,                                     // order 30
        0x00, 0x0a,                                     // preference 10
        0x01,                                           // flag len 1
        0x53,                                           // flag S
        0x08,                                           // service len 8
        0x53, 0x49, 0x50, 0x53, 0x2b, 0x44, 0x32, 0x54, // SIPS+D2T
        0x00,                                           //regex 0
        0x05, 0x5f, 0x73, 0x69, 0x70, 0x73, 0x04, 0x5f, 0x74, 0x63, 0x70, 0x03, 0x73,
        0x69, 0x70, 0x0d, 0x73, 0x74, 0x61, 0x67, 0x65, 0x2d, 0x75, 0x73, 0x32, 0x2d,
        0x74, 0x6e, 0x78, 0x06, 0x74, 0x77, 0x69, 0x6c, 0x69, 0x6f, 0x03, 0x63, 0x6f,
        0x6d, 0x00, // replacement: _sips._tcp.sip.stage-us2-tnx.twilio.com
        // Additional 1 - OPT follows a slightly different mechanism
        0x00,                   // rname '.' (root)
        0x00, 0x29,             // rtype 41 (OPT)
        0x02, 0x00,             // class, requestor's UDP payload size (512 bytes)
        0x00, 0x00, 0x00, 0x00, // ttl, extended RCODE and flags
        0x00, 0x00              // rdlen, length of all rdata
    };

    DNSMessage *msg = packet_to_message(packet);
    int num_answers = 3;
    char *decoded_answer;
    char *expected[] = {
        "10 10 \"S\" \"SIP+D2U\" \"\" _sip._udp.sip.stage-us2-tnx.twilio.com.",
        "20 10 \"S\" \"SIP+D2T\" \"\" _sip._tcp.sip.stage-us2-tnx.twilio.com.",
        "30 10 \"S\" \"SIPS+D2T\" \"\" _sips._tcp.sip.stage-us2-tnx.twilio.com."};
    for (int i = 0; i < num_answers; i++)
    {
        decoded_answer = msg->ans[i]->rdata_to_str(msg->ans[i], packet);
        _assert(strcmp(expected[i], decoded_answer) == 0);
    }
    return 0;
}
int test_cert_record_decoding_1(){
    uint8_t packet[] = {
        0x99, 0x42, 0x85, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x04, 0x31, 0x30,
        0x30, 0x31, 0x06, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x0c, 0x61, 0x74, 0x68, 0x65, 0x6e,
        0x61, 0x68, 0x65, 0x61, 0x6c, 0x74, 0x68, 0x03, 0x63, 0x6f, 0x6d, 0x00, 0x00, 0x25, 0x00,
        0x01, 0xc0, 0x0c, 0x00, 0x25, 0x00, 0x01, 0x00, 0x00, 0x0e, 0x10, 0x04, 0xad, 0x00, 0x01,
        0x00, 0x00, 0x00, 0x30, 0x82, 0x04, 0xa4, 0x30, 0x82, 0x03, 0x8c, 0xa0, 0x03, 0x02, 0x01,
        0x02, 0x02, 0x0a, 0x2f, 0x39, 0x40, 0xfe, 0x00, 0x02, 0x00, 0x00, 0x30, 0x63, 0x30, 0x0d,
        0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x0b, 0x05, 0x00, 0x30, 0x4b,
        0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x55, 0x53, 0x31, 0x19,
        0x30, 0x17, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x10, 0x41, 0x74, 0x68, 0x65, 0x6e, 0x61,
        0x68, 0x65, 0x61, 0x6c, 0x74, 0x68, 0x20, 0x49, 0x6e, 0x63, 0x31, 0x21, 0x30, 0x1f, 0x06,
        0x03, 0x55, 0x04, 0x03, 0x13, 0x18, 0x41, 0x74, 0x68, 0x65, 0x6e, 0x61, 0x68, 0x65, 0x61,
        0x6c, 0x74, 0x68, 0x20, 0x44, 0x69, 0x72, 0x65, 0x63, 0x74, 0x20, 0x43, 0x41, 0x2d, 0x32,
        0x30, 0x1e, 0x17, 0x0d, 0x31, 0x36, 0x30, 0x36, 0x32, 0x39, 0x30, 0x37, 0x31, 0x35, 0x33,
        0x30, 0x5a, 0x17, 0x0d, 0x31, 0x39, 0x30, 0x36, 0x32, 0x39, 0x30, 0x37, 0x31, 0x35, 0x33,
        0x30, 0x5a, 0x30, 0x62, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02,
        0x55, 0x53, 0x31, 0x2c, 0x30, 0x2a, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x23, 0x4d, 0x61,
        0x6c, 0x68, 0x6f, 0x74, 0x72, 0x61, 0x20, 0x43, 0x65, 0x6e, 0x74, 0x65, 0x72, 0x20, 0x66,
        0x6f, 0x72, 0x20, 0x50, 0x6c, 0x61, 0x73, 0x74, 0x69, 0x63, 0x20, 0x53, 0x75, 0x72, 0x67,
        0x65, 0x72, 0x79, 0x31, 0x25, 0x30, 0x23, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x1c, 0x31,
        0x30, 0x30, 0x31, 0x2e, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x2e, 0x61, 0x74, 0x68, 0x65,
        0x6e, 0x61, 0x68, 0x65, 0x61, 0x6c, 0x74, 0x68, 0x2e, 0x63, 0x6f, 0x6d, 0x30, 0x82, 0x01,
        0x22, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01, 0x05,
        0x00, 0x03, 0x82, 0x01, 0x0f, 0x00, 0x30, 0x82, 0x01, 0x0a, 0x02, 0x82, 0x01, 0x01, 0x00,
        0xb0, 0x58, 0xd9, 0x9e, 0x24, 0xa3, 0x52, 0x66, 0xff, 0x92, 0x62, 0x95, 0x73, 0xe4, 0x3e,
        0xcf, 0x2b, 0xf1, 0xb6, 0x28, 0x09, 0xdf, 0xa2, 0x9f, 0x64, 0xb0, 0xde, 0xd7, 0x6b, 0x4f,
        0x84, 0x6d, 0xd0, 0xb5, 0xe0, 0x9d, 0x0d, 0xe9, 0x9a, 0x34, 0x75, 0xbe, 0x9d, 0xa5, 0xa1,
        0xd7, 0xc4, 0xb5, 0x96, 0xb7, 0x51, 0xca, 0xe5, 0xa8, 0xd5, 0x95, 0x8d, 0x50, 0xce, 0x26,
        0x3b, 0xe1, 0x60, 0x0d, 0xb4, 0x15, 0xcb, 0x65, 0xa6, 0x71, 0x76, 0xf5, 0x7f, 0x46, 0x2e,
        0x71, 0x9a, 0x8b, 0xa1, 0x86, 0x71, 0x19, 0xce, 0x8e, 0x63, 0xaa, 0x4f, 0x14, 0xa4, 0x2a,
        0x45, 0x0d, 0x35, 0x20, 0xc6, 0x61, 0xc7, 0x1b, 0x13, 0x3f, 0x2e, 0x30, 0xed, 0x8a, 0x6b,
        0x50, 0x67, 0x68, 0x9b, 0xbb, 0x7d, 0x4c, 0x36, 0x92, 0x62, 0x8d, 0x98, 0xaa, 0xbd, 0xc2,
        0xf1, 0x46, 0x87, 0x20, 0x8a, 0x40, 0x75, 0x29, 0x7a, 0x0e, 0x5a, 0xfe, 0x8e, 0x03, 0x0d,
        0xc9, 0x93, 0xdf, 0x05, 0x81, 0xfa, 0x34, 0xe3, 0x1e, 0x68, 0x44, 0xa1, 0x10, 0x2a, 0x52,
        0xbb, 0x15, 0x73, 0xd5, 0x02, 0xca, 0x1f, 0xa7, 0xc9, 0x8f, 0x0e, 0x57, 0x47, 0x4e, 0x12,
        0x21, 0xfe, 0x39, 0x98, 0xe2, 0x01, 0xa6, 0x35, 0x13, 0x24, 0xf3, 0xa6, 0x7e, 0x81, 0x7b,
        0xab, 0x48, 0x08, 0x72, 0x2e, 0xa0, 0x04, 0x11, 0x4b, 0x68, 0x87, 0x8b, 0xa7, 0x83, 0x25,
        0xbf, 0xae, 0xa7, 0xc8, 0x7a, 0x8d, 0xb4, 0x4c, 0xff, 0xe7, 0x66, 0x36, 0xf2, 0xab, 0xbd,
        0xbe, 0x4c, 0x86, 0xf7, 0x73, 0x18, 0x3e, 0x12, 0xe9, 0xee, 0xaa, 0x0c, 0x0f, 0x3d, 0x2a,
        0x3a, 0x19, 0xff, 0x7b, 0xaf, 0x56, 0xeb, 0xf3, 0xbe, 0x45, 0xae, 0x77, 0x06, 0xd6, 0x56,
        0x14, 0x71, 0x82, 0x44, 0xc1, 0x12, 0xe0, 0x3e, 0xcb, 0x0f, 0x01, 0xfd, 0xd4, 0xdb, 0xb0,
        0xa5, 0x02, 0x03, 0x01, 0x00, 0x01, 0xa3, 0x82, 0x01, 0x71, 0x30, 0x82, 0x01, 0x6d, 0x30,
        0x0e, 0x06, 0x03, 0x55, 0x1d, 0x0f, 0x01, 0x01, 0xff, 0x04, 0x04, 0x03, 0x02, 0x05, 0xa0,
        0x30, 0x0c, 0x06, 0x03, 0x55, 0x1d, 0x13, 0x01, 0x01, 0xff, 0x04, 0x02, 0x30, 0x00, 0x30,
        0x13, 0x06, 0x03, 0x55, 0x1d, 0x25, 0x04, 0x0c, 0x30, 0x0a, 0x06, 0x08, 0x2b, 0x06, 0x01,
        0x05, 0x05, 0x07, 0x03, 0x04, 0x30, 0x34, 0x06, 0x03, 0x55, 0x1d, 0x20, 0x04, 0x2d, 0x30,
        0x2b, 0x30, 0x0d, 0x06, 0x0b, 0x2b, 0x06, 0x01, 0x04, 0x01, 0x82, 0xc1, 0x5b, 0x00, 0x01,
        0x02, 0x30, 0x0c, 0x06, 0x0a, 0x2b, 0x06, 0x01, 0x04, 0x01, 0x82, 0xc1, 0x5b, 0x01, 0x03,
        0x30, 0x0c, 0x06, 0x0a, 0x2b, 0x06, 0x01, 0x04, 0x01, 0x82, 0xc1, 0x5b, 0x02, 0x01, 0x30,
        0x27, 0x06, 0x03, 0x55, 0x1d, 0x11, 0x04, 0x20, 0x30, 0x1e, 0x82, 0x1c, 0x31, 0x30, 0x30,
        0x31, 0x2e, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x2e, 0x61, 0x74, 0x68, 0x65, 0x6e, 0x61,
        0x68, 0x65, 0x61, 0x6c, 0x74, 0x68, 0x2e, 0x63, 0x6f, 0x6d, 0x30, 0x1d, 0x06, 0x03, 0x55,
        0x1d, 0x0e, 0x04, 0x16, 0x04, 0x14, 0x03, 0xf2, 0x23, 0xad, 0x34, 0x1f, 0x30, 0xeb, 0x3d,
        0x63, 0xcd, 0xca, 0x33, 0xf0, 0xf7, 0x84, 0x0b, 0x1b, 0xb1, 0x74, 0x30, 0x1f, 0x06, 0x03,
        0x55, 0x1d, 0x23, 0x04, 0x18, 0x30, 0x16, 0x80, 0x14, 0xa9, 0xed, 0x40, 0x6f, 0xf2, 0x73,
        0x58, 0x6b, 0x04, 0x05, 0x52, 0xf9, 0x29, 0xf0, 0xfb, 0x1d, 0x76, 0x0b, 0xe8, 0x2a, 0x30,
        0x46, 0x06, 0x03, 0x55, 0x1d, 0x1f, 0x04, 0x3f, 0x30, 0x3d, 0x30, 0x3b, 0xa0, 0x39, 0xa0,
        0x37, 0x86, 0x35, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x70, 0x6b, 0x69, 0x2e, 0x61,
        0x74, 0x68, 0x65, 0x6e, 0x61, 0x68, 0x65, 0x61, 0x6c, 0x74, 0x68, 0x2e, 0x63, 0x6f, 0x6d,
        0x2f, 0x41, 0x74, 0x68, 0x65, 0x6e, 0x61, 0x68, 0x65, 0x61, 0x6c, 0x74, 0x68, 0x44, 0x69,
        0x72, 0x65, 0x63, 0x74, 0x43, 0x41, 0x32, 0x2e, 0x63, 0x72, 0x6c, 0x30, 0x51, 0x06, 0x08,
        0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x01, 0x01, 0x04, 0x45, 0x30, 0x43, 0x30, 0x41, 0x06,
        0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x30, 0x02, 0x86, 0x35, 0x68, 0x74, 0x74, 0x70,
        0x3a, 0x2f, 0x2f, 0x70, 0x6b, 0x69, 0x2e, 0x61, 0x74, 0x68, 0x65, 0x6e, 0x61, 0x68, 0x65,
        0x61, 0x6c, 0x74, 0x68, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x41, 0x74, 0x68, 0x65, 0x6e, 0x61,
        0x68, 0x65, 0x61, 0x6c, 0x74, 0x68, 0x44, 0x69, 0x72, 0x65, 0x63, 0x74, 0x43, 0x41, 0x32,
        0x2e, 0x63, 0x72, 0x74, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01,
        0x01, 0x0b, 0x05, 0x00, 0x03, 0x82, 0x01, 0x01, 0x00, 0x27, 0x20, 0xb0, 0xca, 0x42, 0xd2,
        0x0b, 0xd8, 0x8c, 0xfe, 0x97, 0x41, 0xfb, 0x0f, 0xfd, 0xb5, 0x1c, 0xf9, 0x5c, 0x7b, 0xa5,
        0x86, 0xd3, 0x1d, 0x74, 0x7a, 0x1e, 0xb3, 0x2b, 0x45, 0x70, 0xb1, 0x61, 0x01, 0x44, 0x6c,
        0xf0, 0x3c, 0xf9, 0x6c, 0xf7, 0xfa, 0xb4, 0x87, 0x21, 0x9e, 0x29, 0xa8, 0xdf, 0xad, 0xaf,
        0x6b, 0xcd, 0x22, 0x83, 0x2c, 0xee, 0xd1, 0x4e, 0xa9, 0x4b, 0x93, 0x3c, 0x5d, 0xa4, 0x8a,
        0x32, 0xa0, 0x86, 0x15, 0x26, 0x23, 0x5d, 0x47, 0xc0, 0xb5, 0xd9, 0xcd, 0x99, 0xcc, 0x63,
        0x11, 0xbe, 0xf4, 0x95, 0x74, 0x8a, 0xa3, 0x77, 0x62, 0xc0, 0xdf, 0xc8, 0xe6, 0x84, 0x5f,
        0xc6, 0x55, 0x8c, 0x6f, 0x54, 0x47, 0x1c, 0xf4, 0x0b, 0x46, 0xba, 0xe0, 0xf7, 0x2a, 0xdf,
        0xb9, 0x1c, 0xd7, 0x0e, 0x38, 0x9c, 0x5e, 0x90, 0x8d, 0x53, 0xdb, 0x2d, 0xdf, 0x24, 0xea,
        0xf5, 0x3a, 0x22, 0x57, 0x71, 0x3e, 0xf0, 0x95, 0xc3, 0x5a, 0xad, 0xd5, 0x5d, 0x01, 0x26,
        0xf9, 0xb0, 0xac, 0xd9, 0xff, 0x7f, 0x0f, 0x30, 0x40, 0x74, 0xe1, 0xb3, 0x05, 0x3d, 0xf3,
        0x3a, 0x8c, 0xe6, 0x47, 0x98, 0x7b, 0x65, 0x97, 0x72, 0x1a, 0xe6, 0xaf, 0xb4, 0x78, 0xe1,
        0x52, 0x0f, 0x5d, 0x0e, 0x5c, 0xe2, 0xc0, 0xf4, 0x9e, 0xd6, 0xf0, 0xe4, 0xf2, 0x24, 0xc3,
        0x06, 0x30, 0xb9, 0xca, 0xae, 0x42, 0x70, 0x7c, 0x94, 0xef, 0x67, 0xa7, 0xbd, 0xc9, 0x89,
        0xc1, 0x98, 0x74, 0x27, 0x31, 0x80, 0x2b, 0x5b, 0x9e, 0x08, 0xf7, 0xa2, 0x36, 0xef, 0xd9,
        0xf9, 0x4b, 0x47, 0x19, 0xf8, 0x0c, 0x33, 0x8e, 0x8f, 0x83, 0x41, 0x26, 0x37, 0xe3, 0xd2,
        0x64, 0x44, 0x51, 0xbb, 0x9a, 0x6d, 0x97, 0x46, 0xf9, 0x72, 0x20, 0xf0, 0xbf, 0xf2, 0x1d,
        0x77, 0xf0, 0xed, 0x53, 0x34, 0x05, 0xea, 0x7b, 0x12, 0x25, 0x00, 0x00, 0x29, 0x10, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    DNSMessage *msg = packet_to_message(packet);
    char *decoded_answer;
    char *expected =
        "1 0 0 MIIEpDCCA4ygAwIBAgIKLzlA/gACAAAwYzANBgkqhkiG9w0BAQsFADBLMQswCQYDVQQGEwJVUzEZMBc"
        "GA1UEChMQQXRoZW5haGVhbHRoIEluYzEhMB8GA1UEAxMYQXRoZW5haGVhbHRoIERpcmVjdCBDQS0yMB4XDTE2MDY"
        "yOTA3MTUzMFoXDTE5MDYyOTA3MTUzMFowYjELMAkGA1UEBhMCVVMxLDAqBgNVBAoTI01hbGhvdHJhIENlbnRlci"
        "Bmb3IgUGxhc3RpYyBTdXJnZXJ5MSUwIwYDVQQDExwxMDAxLmRpcmVjdC5hdGhlbmFoZWFsdGguY29tMIIBIjANB"
        "gkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAsFjZniSjUmb/kmKVc+Q+zyvxtigJ36KfZLDe12tPhG3QteCdDemaN"
        "HW+naWh18S1lrdRyuWo1ZWNUM4mO+FgDbQVy2WmcXb1f0YucZqLoYZxGc6OY6pPFKQqRQ01IMZhxxsTPy4w7Ypr"
        "UGdom7t9TDaSYo2Yqr3C8UaHIIpAdSl6Dlr+jgMNyZPfBYH6NOMeaEShECpSuxVz1QLKH6fJjw5XR04SIf45mOIB"
        "pjUTJPOmfoF7q0gIci6gBBFLaIeLp4Mlv66nyHqNtEz/52Y28qu9vkyG93MYPhLp7qoMDz0qOhn/e69W6/O+Ra5"
        "3BtZWFHGCRMES4D7LDwH91NuwpQIDAQABo4IBcTCCAW0wDgYDVR0PAQH/BAQDAgWgMAwGA1UdEwEB/wQCMAAwEwY"
        "DVR0lBAwwCgYIKwYBBQUHAwQwNAYDVR0gBC0wKzANBgsrBgEEAYLBWwABAjAMBgorBgEEAYLBWwEDMAwGCisGAQ"
        "QBgsFbAgEwJwYDVR0RBCAwHoIcMTAwMS5kaXJlY3QuYXRoZW5haGVhbHRoLmNvbTAdBgNVHQ4EFgQUA/IjrTQfM"
        "Os9Y83KM/D3hAsbsXQwHwYDVR0jBBgwFoAUqe1Ab/JzWGsEBVL5KfD7HXYL6CowRgYDVR0fBD8wPTA7oDmgN4Y1a"
        "HR0cDovL3BraS5hdGhlbmFoZWFsdGguY29tL0F0aGVuYWhlYWx0aERpcmVjdENBMi5jcmwwUQYIKwYBBQUHAQEE"
        "RTBDMEEGCCsGAQUFBzAChjVodHRwOi8vcGtpLmF0aGVuYWhlYWx0aC5jb20vQXRoZW5haGVhbHRoRGlyZWN0Q0Ey"
        "LmNydDANBgkqhkiG9w0BAQsFAAOCAQEAJyCwykLSC9iM/pdB+w/9tRz5XHulhtMddHoesytFcLFhAURs8Dz5bPf"
        "6tIchnimo362va80igyzu0U6pS5M8XaSKMqCGFSYjXUfAtdnNmcxjEb70lXSKo3diwN/I5oRfxlWMb1RHHPQLRrr"
        "g9yrfuRzXDjicXpCNU9st3yTq9ToiV3E+8JXDWq3VXQEm+bCs2f9/DzBAdOGzBT3zOozmR5h7ZZdyGuavtHjhUg"
        "9dDlziwPSe1vDk8iTDBjC5yq5CcHyU72envcmJwZh0JzGAK1ueCPeiNu/Z+UtHGfgMM46Pg0EmN+PSZERRu5ptl0"
        "b5ciDwv/Idd/DtUzQF6nsSJQ==";
    decoded_answer = msg->ans[0]->rdata_to_str(msg->ans[0], packet);
    _assert(strcmp(expected, decoded_answer) == 0);
    return 0;
}

/*======================================================================================================================*/
// Helper functions
void printf_encoded_name(char *encoded_name)
{
    for (int i = 0; i < strlen(encoded_name); i++)
    {
        printf("%c(%d) ", encoded_name[i], encoded_name[i]);
    }
    printf("\n");
}

int cmp_u16array(uint16_t *array1, uint16_t *array2, int num_elements)
{
    for (int i = 0; i < num_elements; i++)
    {
        if (array1[i] != array2[i])
        {
            //printf("Diff found at index %d: %04X %04X", i, array1[i], array2[i]);
            return 1;
        }
    }
    return 0;
}

int cmparray(uint8_t *array1, uint8_t *array2, int num_elements)
{
    for (int i = 0; i < num_elements; i++)
    {
        if (array1[i] != array2[i])
        {
            //printf("Diff found at index %d: %02X %02X ", i, array1[i], array2[i]);
            return 1;
        }
    }
    return 0;
}

void print_arrays(uint8_t *array1, uint8_t *array2, uint32_t num_elements)
{
    for (uint32_t i = 0; i < num_elements; i += 2)
    {
        if (i + 2 < num_elements)
        {
            printf("%02X %02X || %02X %02X\n",
                   array1[i], array1[i + 1],
                   array2[i], array2[i + 1]);
        }
        else
        {
            printf("%02X    || %02X\n",
                   array1[i], array2[i]);
        }
    }
}
