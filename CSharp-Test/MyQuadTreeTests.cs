﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DataStructures;

namespace CSharp.Tests;

internal class TestPoint : IPoint
{
    public bool WasChecked = false;
    private readonly double _x;
    private readonly double _y;

    public TestPoint(double x, double y, string data = "")
    {
        _x = x;
        _y = y;
        Data = data;
    }

    public readonly string Data;

    public double X
    {
        get
        {
            WasChecked = true;
            return _x;
        }
    }

    public double Y
    {
        get
        {
            WasChecked = true;
            return _y;
        }
    }

    public override bool Equals(object? obj)
    {
        WasChecked = true;
        return base.Equals(obj);
    }

    public static bool operator ==(TestPoint a, TestPoint b)
    {
        a!.WasChecked = true;
        b!.WasChecked = true;
        return a.Equals(b);
    }

    public static bool operator !=(TestPoint a, TestPoint b) => !(a == b);

    public static TestPoint CreateRandom()
    {
        var randomString = Guid.NewGuid().ToString();
        var x = Random.Shared.NextDouble() * 24 - 12;
        var y = Random.Shared.NextDouble() * 24 - 12;
        return new TestPoint(x, y, randomString);
    }
}

internal class MyQuadTreeTests
{

    [Test]
    public void Debug()
    {
        var quadTree = new MyQuadTree<TestPoint>();
        for (var i = 0; i < 100; i++)
        {
            var point = TestPoint.CreateRandom();
            quadTree.Add(point);
        }
    }

    [Test]
    public void WhenConstructing_ShouldBeEmpty()
    {
        var quadTree = new MyQuadTree<TestPoint>();
        Assert.That(quadTree.Length, Is.EqualTo(0));
    }

    [Test]
    public void WhenAddingPoint_ShouldContainPoint()
    {
        var quadTree = new MyQuadTree<TestPoint>();
        var point = new TestPoint(5, 10, "hi");

        quadTree.Add(point);
        Assert.True(quadTree.Contains(point));
    }

    [Test]
    public void WhenAddingPoint_ShouldIncreaseLength()
    {
        var quadTree = new MyQuadTree<TestPoint>();
        var point = new TestPoint(5, 10, "hi");

        quadTree.Add(point);
        Assert.That(quadTree.Length, Is.EqualTo(1));
    }

    [Test]
    public void WhenRemovingPoint_ShouldNotContainPoint()
    {
        var quadTree = new MyQuadTree<TestPoint>();
        var point = new TestPoint(5, 10, "hi");
        quadTree.Add(point);

        quadTree.Remove(point);
        Assert.False(quadTree.Contains(point));
    }

    [Test]
    public void WhenClearing_ShouldBeEmpty()
    {
        var quadTree = new MyQuadTree<TestPoint>();
        var point1 = new TestPoint(5, 10, "hi");
        var point2 = new TestPoint(10, 5, "bye");
        quadTree.Add(point1);
        quadTree.Add(point2);

        quadTree.Clear();
        Assert.That(quadTree.Length, Is.EqualTo(0));
    }

    [Test]
    public void WhenFindInRange_ShouldReturnAllInRange()
    {
        var quadTree = new MyQuadTree<TestPoint>();
        var x1y1 = new TestPoint(1, 1, "center");
        var x1y1_99 = new TestPoint(1, 1.99, "just in range");
        var x2y2 = new TestPoint(2, 2, "just out of range");
        var x1y10 = new TestPoint(1, 10, "out of range");
        var x10y1 = new TestPoint(10, 1, "out of range");
        var x5y5 = new TestPoint(5, 5, "out of range");
        quadTree.Add(x1y1);
        quadTree.Add(x1y1_99);
        quadTree.Add(x2y2);
        quadTree.Add(x1y10);
        quadTree.Add(x10y1);
        quadTree.Add(x5y5);

        var found = quadTree.FindRange(1, 1, 1).ToArray();
        Assert.That(found, Is.EquivalentTo(new[] { x1y1 , x1y1_99 }));
    }

    [Test]
    public void WhenFindingNearest_ShouldReturnNearest()
    {
        var quadTree = new MyQuadTree<TestPoint>();
        var x1y1 = new TestPoint(1, 1, "a");
        var x2y2 = new TestPoint(2, 2, "b");
        var x1y10 = new TestPoint(1, 10, "c");
        var x10y1 = new TestPoint(10, 1, "d");
        var x5y5 = new TestPoint(5, 5, "e");
        quadTree.Add(x1y1);
        quadTree.Add(x2y2);
        quadTree.Add(x1y10);
        quadTree.Add(x10y1);
        quadTree.Add(x5y5);

        var found = quadTree.FindNearest(3, 3);
        Assert.That(found, Is.EqualTo(x2y2));
    }

    #region peformance
    [Test]
    [TestCase(5,5)]
    [TestCase(100, 30)]
    [TestCase(1000, 40)]
    [TestCase(10000, 50)]
    [TestCase(100000, 60)]
    [Parallelizable(ParallelScope.Self)]
    public void WhenFindingNearest_ShouldNotCheckMostPoints(int numPoints,int maxAllowed)
    {
        // Before: Create Random Quad Tree
        var quadTree = new MyQuadTree<TestPoint>();
        var points = new List<TestPoint>();
        for (var i = 0; i < numPoints; i++)
        {
            var point = TestPoint.CreateRandom();
            quadTree.Add(point);
            points.Add(point);
        }

        // Before: Create Expected Outcome
        var expectedNearestPoint = points.MinBy(p => p.Distance(5, 5));

        foreach (var point in points)        
            point.WasChecked = false;

        // Run Test
        var actualNearestPoint = quadTree.FindNearest(5,5);

        // Assert
        var pointsChecked = points.Count(p => p.WasChecked);
        Assert.That(pointsChecked, Is.LessThanOrEqualTo(maxAllowed));
        Assert.That(actualNearestPoint, Is.EqualTo(expectedNearestPoint));
    }

    [Test]
    [TestCase(5)]
    [TestCase(100)]
    [TestCase(1000)]
    [TestCase(10000)]
    [TestCase(100000)]
    [Parallelizable(ParallelScope.Self)]
    public void WhenFindingRange_ShouldNotCheckMostPoints(int numPoints)
    {
        const double range = 1;
        // Before: Create Random Quad Tree
        var quadTree = new MyQuadTree<TestPoint>();
        var points = new List<TestPoint>();
        for (var i = 0; i < numPoints; i++)
        {
            var point = TestPoint.CreateRandom();
            quadTree.Add(point);
            points.Add(point);
        }

        // Before: Create Expected Outcome
        var firstPoint = points[0];
        var expectedPointsInRange = points.Where(p => p.Distance(firstPoint) < range).ToArray();
        var maxAllowedChecks = (expectedPointsInRange.Length * 2) + (MathF.Log2(numPoints) * 2) + 10; // Allowed number of checks can be changed based on your nonfunctional requirements

        foreach (var point in points)
            point.WasChecked = false;

        // Run Test
        var actualPointsInRange = quadTree.FindRange(firstPoint.X, firstPoint.Y, range).ToArray();


        // Assert
        var pointsChecked = points.Count(p => p.WasChecked);
        Assert.That(actualPointsInRange, Is.EquivalentTo(expectedPointsInRange));
        Assert.That(pointsChecked, Is.LessThanOrEqualTo(maxAllowedChecks));
    }
    #endregion

}

