#include "gtest/gtest.h"
#include "gmock/gmock.h"

class Goo
{
public:
	Goo() = default;
	virtual ~Goo() = default;

	virtual bool DoStuff()
	{
		return true;
	}
};

class MockGoo : public Goo
{
	public:
		MOCK_METHOD0(DoStuff, bool());
};

Goo *goo = new Goo();

class Foo
{
public:
	Foo() = default;

	virtual ~Foo()
	{
		goo->DoStuff();
	}
};

class FooTest : public testing::Test
{
protected:
	MockGoo mockGoo;
	Foo     *foo;
public:
	virtual void SetUp()
	{
		goo = &mockGoo;
		foo = new Foo();
	}

	virtual void TearDown()
 	{
		delete foo;
	}

};

TEST_F(FooTest, DoesNotDoStuff)
{
	EXPECT_CALL(mockGoo, DoStuff())
		.Times(0);
}