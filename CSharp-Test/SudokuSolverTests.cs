using CSharp.Tests;
using DataStructures;
using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp.Test;

internal class SudokuSolverTests
{
    public int[,] StringToMultidimensionalArray(string input)
    {
        var rows = input.Split('\n');
        int[,] result = new int[rows.Length, rows[0].Split(',').Length];

        for (int i = 0; i < rows.Length; i++)
        {
            var elements = rows[i].Split(',');
            for (int j = 0; j < elements.Length; j++)
            {
                result[i, j] = int.Parse(elements[j]);
            }
        }

        return result;
    }

    public string MultidimensionalArrayToString(int[,] board)
    {
        var sb = new StringBuilder();
        for(var r = 0; r < board.GetLength(0); ++r)
        {
            for (var c = 0; c < board.GetLength(1); ++c)
            {
                sb.Append(board[r, c]);
                sb.Append(",");
            }
            sb.Length--;
            sb.Append("\n");
        }
        return sb.ToString();
    }

    [TestCase(
        "5,3,0,0,7,0,0,0,0\n" +
        "6,0,0,1,9,5,0,0,0\n" +
        "0,9,8,0,0,0,0,6,0\n" +
        "8,0,0,0,6,0,0,0,3\n" +
        "4,0,0,8,0,3,0,0,1\n" +
        "7,0,0,0,2,0,0,0,6\n" +
        "0,6,0,0,0,0,2,8,0\n" +
        "0,0,0,4,1,9,0,0,5\n" +
        "0,0,0,0,8,0,0,7,9")]
    public void WhenValidBoard_ShouldSolve(string boardStr)
    {
        var board = StringToMultidimensionalArray(boardStr);
        var solver = new MySudokuSolverWaveFunctionCollapseNoAlloc();
        var wasSuccessful = solver.Solve(board); 
        Assert.IsTrue(wasSuccessful);   
        Console.WriteLine(MultidimensionalArrayToString(board));
    }


}
