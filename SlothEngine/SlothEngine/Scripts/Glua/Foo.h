class Test;

class Foo
{
    enum class Thing
    {
        kOther,
    };

public:

        GLUA()
        int Test(int myInt);

        GLUA()
        Test* GetTestPointer(const int someArg, float somethingElse);

		GLUA()
		void FunctionThatDoesNothing();
}