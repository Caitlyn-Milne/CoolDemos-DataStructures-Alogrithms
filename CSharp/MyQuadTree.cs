using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices.ComTypes;
using System.Text;
using System.Threading.Tasks;

namespace DataStructures;

public interface IPoint
{
    public double X { get; }
    public double Y { get; }
}

public interface IQuadTree<T>
    where T : IPoint
{
    public void Add(T point);
    public void Remove(T point);
    public void Clear();
    public bool Contains(T point);
    public T? FindNearest(double x, double y);

    public IEnumerable<T> FindRange(double x, double y, double range);

    public int Length { get; }

    public int QuadCapacity { get; }
}

public class MyQuadTree<T> : IQuadTree<T> where T : IPoint
{
    private MyQuad<T> _root;

    public MyQuadTree()
    {
        _root = new MyQuad<T>(this, new Boundary(-100, 100, -100, 100)); //todo auto grow
    }

    public void Add(T point)
    {
        Length++;
        _root.Add(point);
    }

    public void Remove(T point)
    {
        Length--;
        throw new NotImplementedException();
    }

    public void Clear()
    {
        Length = 0;
        _root = new MyQuad<T>(this, _root.Bounds);
    }

    public bool Contains(T point)
    {
        return _root.Contains(point);
    }

    public T? FindNearest(double x, double y)
    {
        throw new NotImplementedException();
    }

    public IEnumerable<T> FindRange(double x, double y, double range)
    {
        throw new NotImplementedException();
    }

    public int Length { get; private set; }
    public int QuadCapacity => 4;
}

internal class Boundary
{
    public Boundary(double xMin, double xMax, double yMin, double yMax)
    {
        XMin = xMin;
        XMax = xMax;
        YMin = yMin;
        YMax = yMax;
    }

    public double XMin { get; init; }
    public double XMax { get; init; }
    public double YMin { get; init; }
    public double YMax { get; init; }

    public double XMid => (XMin + XMax) / 2;
    public double YMid => (YMin + YMax) / 2;

    public bool Contains(double x, double y)
    {
        return XMin <= x && x < XMax 
            && YMin <= y && y < YMax;
    }
}

internal class MyQuad<T> where T : IPoint
{
    public readonly MyQuadTree<T> Source;
    public readonly Boundary Bounds;

    private readonly List<T> _points = new();
    private MyQuad<T>[] _children = Array.Empty<MyQuad<T>>();

    public MyQuad(MyQuadTree<T> source, Boundary bounds)
    {
        Source = source;
        Bounds = bounds;
    }

    public bool Contains(T point)
    {
        if (!Bounds.Contains(point.X, point.Y)) return false;
        if (_children.Length == 0) return _points.Contains(point);
        return _children.Any(child => child.Contains(point));
    }

    public void Add(T point)
    {
        if (_children.Length == 0)
        {
            _points.Add(point);
            if (_points.Count > Source.QuadCapacity)
            {
                Quadify();
            }
            return;
        }
        foreach (var child in _children)
        {
            if (!child.Bounds.Contains(point.X, point.Y)) continue;
            child.Add(point);
            break;
        }
    }

    private void Quadify()
    {
        _children = new MyQuad<T>[4];
        _children[0] = CreateChild(Bounds.XMin, Bounds.XMid, Bounds.YMid, Bounds.YMax); //top left
        _children[1] = CreateChild(Bounds.XMid, Bounds.XMax, Bounds.YMid, Bounds.YMax); //top right
        _children[2] = CreateChild(Bounds.XMin, Bounds.XMid, Bounds.YMin, Bounds.YMid); //bottom left
        _children[3] = CreateChild(Bounds.XMid, Bounds.XMax, Bounds.YMin, Bounds.YMid); //bottom right

        foreach (var point in _points)
        {
            foreach (var child in _children)
            {
                if (!child.Bounds.Contains(point.X, point.Y)) continue;
                child.Add(point);
                break;
            }
        }
        _points.Clear();
        _points.Capacity = 0;
    }

    private MyQuad<T> CreateChild(double xMin, double xMax, double yMin, double yMax)
    {
        var bounds = new Boundary(xMin, xMax, yMin, yMax);
        return new MyQuad<T>(Source, bounds);
    }

}
