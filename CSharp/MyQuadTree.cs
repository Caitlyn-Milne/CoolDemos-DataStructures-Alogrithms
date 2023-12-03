using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices.ComTypes;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace DataStructures;

public static class PointHelpers
{
    public static double Distance(double x1, double y1, double x2, double y2)
    {
        return Math.Sqrt(Math.Pow(x1 - x2, 2) + Math.Pow(y1 - y2, 2));

    }

    public static double Distance(this IPoint point1, IPoint point2)
    {
        return Distance(point1.X, point1.Y, point2.X, point2.Y);
    }

    public static double Distance(this IPoint point1, double x, double y)
    {
        return Distance(point1.X, point1.Y, x, y);
    }
}

public interface IPoint
{
    public double X { get; }
    public double Y { get; }
}

public interface IQuadTree<T>
    where T : IPoint
{
    public void Add(T point);
    public bool Remove(T point);
    public void Clear();
    public bool Contains(T point);
    public T? FindNearest(double x, double y);

    public IEnumerable<T> FindRange(double x, double y, double exclusiveRangee);

    public int Length { get; }

    public int QuadCapacity { get; }
}

public class MyQuadTree<T> : IQuadTree<T> where T : IPoint
{
    private MyQuad<T> _root;

    public MyQuadTree()
    {
        _root = new MyQuad<T>(QuadCapacity, new Boundary(-12, 12, -12, 12)); //todo auto grow
    }

    public void Add(T point)
    {
        Length++;
        _root.Add(point);
    }

    public bool Remove(T point)
    {
        Length--;
        return _root.Remove(point);
    }

    public void Clear()
    {
        Length = 0;
        _root = new MyQuad<T>(QuadCapacity, _root.Bounds);
    }

    public bool Contains(T point)
    {
        return _root.Contains(point);
    }

    public T? FindNearest(double x, double y)
    {
        throw new NotImplementedException();
    }

    public IEnumerable<T> FindRange(double x, double y, double exclusiveRange)
    {
        return _root.FindRange(x, y, exclusiveRange);
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

    public (double x, double y) ClosestPoint(double x, double y)
    {
        return (Math.Clamp(x, XMin, XMax), Math.Clamp(y, YMin, YMax));
    }

    public override string ToString()
    {
        return $"{XMin},{YMin} {XMax},{YMax}";
    }
}

internal class MyQuad<T> where T : IPoint
{
    public readonly int Capacity;
    public readonly Boundary Bounds;

    private readonly List<T> _points = new();
    private MyQuad<T>[] _children = Array.Empty<MyQuad<T>>();
    private int Count;

    public MyQuad(int capacity, Boundary bounds)
    {
        Capacity = capacity;
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
        Count++;
        if (_children.Length == 0)
        {
            _points.Add(point);
            if (_points.Count > Capacity)       
                Quadify();         
            return;
        }
        foreach (var child in _children)
        {
            if (!child.Bounds.Contains(point.X, point.Y)) continue;
            child.Add(point);
            break;
        }
    }

    public bool Remove(T point)
    {
        Count--;
        if (_children.Length == 0) 
        { 
            return _points.Remove(point);
        }
        foreach (var child in _children)
        {
            if (child.Contains(point)) 
                return child.Remove(point);
        }
        return false;
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
        return new MyQuad<T>(Capacity, bounds);
    }

    public IEnumerable<T> FindRange(double x, double y, double exclusiveRange)
    {
        if(_children.Length == 0)
        {
            foreach(var point in _points)
            {
                if(point.Distance(x, y) < exclusiveRange)
                    yield return point;
            }
            yield break;
        }

        foreach (var child in _children)
        {
            var closestPoint = child.Bounds.ClosestPoint(x, y);
            var distance = PointHelpers.Distance(closestPoint.x, closestPoint.y, x, y);
            if (distance > exclusiveRange) continue;
            foreach(var childResult in child.FindRange(x, y, exclusiveRange))
            {
                yield return childResult;
            }
        }
    }

    public override string ToString()
    {
        return Bounds.ToString();
    }
}
