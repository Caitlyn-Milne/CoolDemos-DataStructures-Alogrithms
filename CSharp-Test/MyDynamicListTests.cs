using DataStructures;

namespace CSharp.Tests;

public class MyDynamicListTests
{
    [Test]
    public void Constructor_Empty_ShouldHaveDefaultCapacity()
    {
        var list = new MyDynamicList<int>();
        Assert.That(list.Capacity, Is.EqualTo(MyDynamicList.DEFAULT_CAPACITY));
    }

    [TestCase(8)]
    [TestCase(1024)]
    [TestCase(0)]
    [TestCase(1)]
    public void Constructor_SetCapacity_ShouldHaveSetCapacity(int capacity)
    {
        var list = new MyDynamicList<int>(capacity);
        Assert.That(list.Capacity, Is.EqualTo(capacity));
    }

    [TestCase(-1)]
    [TestCase(-1024)]
    public void Constructor_SetNegativeCapacity_ShouldThrow(int capacity)
    {
        if (capacity >= 0)
        {
			Assert.Fail("incorrect test set up");
        }

        Assert.Throws<OverflowException>(() =>
        {
            var _ = new MyDynamicList<int>(capacity);
        });
    }

    [TestCase(new int[0], new[] { 1, 2 }, new[] { 1, 2 })]
    [TestCase(new[] { 1, 2 }, new[] { 3 }, new[] { 1, 2, 3 })]
    [TestCase(new[] { 10, 37 }, new[] { 4 }, new[] { 10, 37, 4 })]
    public void Add(int[] startWith, int[] add, int[] expect)
    {
        var list = new MyDynamicList<int>(startWith);
        foreach (var toAdd in add)
        {
            list.Add(toAdd);
        }

        Assert.That(list, Is.EqualTo(expect));
    }

    [TestCase(0)]
    [TestCase(1)]
    [TestCase(10000)]
    [TestCase(1000000)]
    public void Add_Bulk(int amount)
    {
        var list = new MyDynamicList<int>();
		var expect = new int[amount];
        for (var i = 0; i < amount; i++)
        {
            list.Add(i);
            expect[i] = i;
        }
        Assert.That(list, Is.EqualTo(expect));
    }

    [TestCase(new [] { 0, 1, 2 }, new[] { 1 }, new[] { 0, 2 })]
    [TestCase(new[] { 0, 1, 2 }, new[] { 2, 1, 0 }, new int[0])]
    [TestCase(new[] { 0, 1, 2 }, new[] { 0,0 }, new []{ 2 })]
    public void RemoveAt(int[] startWith, int[] removeIndices, int[] expect)
    {
        var list = new MyDynamicList<int>(startWith);
        foreach (var removeIndex in removeIndices)
        {
            list.RemoveAt(removeIndex);
        }
        Assert.That(list, Is.EqualTo(expect));
    }

    [Test]
    public void RemoveAll_AlwaysFalse_ExpectSame()
    {
        var items = new[] { 1, 2, 3 };
        var list = new MyDynamicList<int>(items);
        list.RemoveAll(_ => false);
        Assert.That(list, Is.EqualTo(items));
    }

    [Test]
    public void RemoveAll_AlwaysTrue_ExpectEmpty()
    {
        var items = new[] { 1, 2, 3 };
        var list = new MyDynamicList<int>(items);
        list.RemoveAll(_ => true);
        Assert.That(list, Is.EqualTo(Array.Empty<int>()));
    }

	[Test]
    public void RemoveAll_TrueForEven_ExpectOnlyOdd()
    {
        var expect = new[] { 1, 3, 5 };
        var list = new MyDynamicList<int>(new[] { 1, 2, 3, 4, 5 });
        list.RemoveAll(i => i % 2 == 0);
        Assert.That(list, Is.EqualTo(expect));
    }

    [Test]
    public void Indexer_Get1x2x3_Expect1x2x3()
    {
        var list = new MyDynamicList<int>(new[] { 1, 2, 3 });

        Assert.That(list.Count, Is.EqualTo(3));
        Assert.That(list[0], Is.EqualTo(1));
        Assert.That(list[1], Is.EqualTo(2));
        Assert.That(list[2], Is.EqualTo(3));
    }

    [Test]
    public void Indexer_Set1x2x3To2x4x6_Expect2x4x6()
    {
        var list = new MyDynamicList<int>(new[] { 1, 2, 3 });
        list[0] = 2;
        list[1] = 4;
        list[2] = 6;

        Assert.That(list.Count, Is.EqualTo(3));
        Assert.That(list[0], Is.EqualTo(2));
        Assert.That(list[1], Is.EqualTo(4));
        Assert.That(list[2], Is.EqualTo(6));
    }

    [Test]
    public void Indexer_ExceedsBounds_ExpectThrow()
    {
        var list = new MyDynamicList<int>(new[] { 1, 2, 3 });
        Assert.Throws<IndexOutOfRangeException>(() =>
        {
            _ = list[3];
        });
    }

    [Test]
    public void Indexer_UnderBounds_ExpectThrow()
    {
        var list = new MyDynamicList<int>(new[] { 1, 2, 3 });
        Assert.Throws<IndexOutOfRangeException>(() =>
        {
            _ = list[-1];
        });
    }

    [TestCase(new[] { 1, 2, 3 }, new[] { 0 }, new[] { 0 }, new[] { 0, 1, 2, 3 })]
    [TestCase(new[] { 1, 2, 3 }, new[] { 3 }, new[] { 4 }, new[] { 1, 2, 3, 4 })]
    [TestCase(new[] { 1, 3, 4 }, new[] { 1 }, new[] { 2 }, new[] { 1, 2, 3, 4 })]

    public void Insert(int[] startWith, int[] indexes, int[] values, int[] expect)
    {
        if (indexes.Length != values.Length)
        {
            Assert.Fail("invalid test set up, " +
                        "indexes and values are key value pairs and therefore should have matching lengths");
        }

        var list = new MyDynamicList<int>(startWith);
        for (var i = 0; i < indexes.Length; i++)
        {
            list.Insert(indexes[i], values[i]);
        }
        Assert.That(list, Is.EqualTo(expect));
    }

    [Test]
    public void Insert_AtCapacity_ShouldBe1x2x3()
    {
        var list = new MyDynamicList<int>(3) { 1, 2 };
        list.Insert(2, 3);
        Assert.That(list, Is.EqualTo(new[] {1,2,3}));
    }

    [Test]
    public void Clear_ShouldBeEmpty()
    {
        var list = new MyDynamicList<int>(3) { 1, 2 };
        list.Clear();
        Assert.That(list, Is.Empty);
    }
}