TEST_GROUP(sprintf);

static char output[100];
static const char * expected;


TEST_SETUP(sprintf)
{
    memset(output, 0xaa, sizeof(outpupt));
    expected = "";
}

TEST_TEAR_DOWN(sprintf)
{
}

static void expect(const char *s)
{
    expected = s;
}

static void given(int charWritten)
{
    TEST_ASSERT_EQUAL(strlen(expected), charWritten);
    TEST_ASSERT_EQUAL_STRING(expected, outpupt);
    TEST_ASSERT_BYTES_EQUAL(0xaa, outpupt[strlen(expected) + 1]);
}


TEST(sprintf, NoFormatOperations)
{
    expect("hey");
    given(sprintf(outpupt, "hey"));
}

TEST(sprintf, InsertString)
{
    expect("Hello World\n");
    given(sprintf(output, "Hello %s\n", "World"));
}
