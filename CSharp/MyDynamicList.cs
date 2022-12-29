using System.Collections;

namespace DataStructures;

public class MyDynamicList 
{
    public const int DEFAULT_CAPACITY = 4;
}

public class MyDynamicList<T> : MyDynamicList , IList<T>
{
    public int Count { get; private set; }
    public int Capacity => _array.Length;
    public bool IsReadOnly => false;

    private T?[] _array;

    public MyDynamicList(T[] array)
    {
        var size = array.Length;
        _array = new T[size];
        Array.Copy(array,0,_array,0, size);
        Count = size;
    }

    public MyDynamicList()
    {
        _array = new T[DEFAULT_CAPACITY];
        Count = 0;
    }

    public MyDynamicList(int capacity)
    {
        _array = new T[capacity];
        Count = 0;
    }

    public T this[int index]
    {
        get
        {
            ValidateInBounds(index);
            return _array[index]!;
        }
        set
        {
            ValidateInBounds(index);
            _array[index] = value;
        }
    }

    public IEnumerator<T> GetEnumerator()
    {
        for (var i = 0; i < Count; i++)
        {
            yield return _array[i]!;
        }
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return GetEnumerator();
    }

    public void Add(T item)
    {
        ++Count;
        EnsureCapacity();
        _array[Count - 1] = item;
    }

    private void EnsureCapacity()
    {
        if (Count <= Capacity) return;

        var newCapacity = Capacity * 2; 
        if (newCapacity < 1)
        {
            newCapacity = 1;
        }

        var newArray = new T?[newCapacity];
        for (var i = 0; i < _array.Length; i++)
        {
            newArray[i] = _array[i];
        }
        _array = newArray;
    }

    public void Clear()
    {
        for (var index = 0; index < _array.Length; index++)
        {
            _array[index] = default;
        }
        Count = 0;
    }

    public bool Contains(T item)
    {
        return IndexOf(item) != -1;
    }

    public void CopyTo(T[] array, int arrayIndex)
    {
        for (var index = arrayIndex; index < Count; index++)
        {
            array[index] = _array[index]!;
        }
    }

    public bool Remove(T item)
    {
        var index = IndexOf(item);
        if (index == -1) return false;
        RemoveAt(index);
        return true;
    }

    public int IndexOf(T item)
    {
        for (var i = 0; i < Count; i++)
        {
            if (Equals(_array[i], item)) return i;
        }
        return -1;
    }

    public void Insert(int index, T item)
    {
        Count++;
        EnsureCapacity();
        for (var i = Count - 2; i >= index; i--)
        {
            _array[i + 1] = _array[i];
        }
        _array[index] = item;
    }

    public void RemoveAt(int index)
    {
        RemoveAll((_, i) => i == index);
    }

    public void RemoveAll(Func<T,bool> predicate)
    {
        RemoveAll((item,_) => predicate(item));
    }

    public void RemoveAll(Func<T,int, bool> predicate)
    {
        var left = -1;
        var newCount = 0;
        for (var right = 0; right < Count; right++)
        {
            if (predicate(_array[right]!, right))
            {
                _array[right] = default;
                continue;
            }
            left++;
            newCount++;
            var temp = _array[left];
            _array[left] = _array[right];
            _array[right] = temp;
        }
        Count = newCount;
    }

    public void ValidateInBounds(int index)
    {
        if (0 > index || index >= Count)
        {
            throw new IndexOutOfRangeException();
        }
    }

}