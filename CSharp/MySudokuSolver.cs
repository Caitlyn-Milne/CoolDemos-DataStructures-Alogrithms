using CutelynResults.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp;

internal interface ISudokuSolver
{
    public bool Solve(int[,] board);
}


public class MySudokuSolverWaveFunctionCollapseNoAlloc : ISudokuSolver
{
    const int UncollapsedMask = 1 << 9;
    const int AllSuperPositionsMask = 1 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6 | 1 << 7 | 1 << 8 | UncollapsedMask;

    public bool Solve(int[,] board)
    {
        if (!BasicValidate(board)) return false;

        // Push data into specific bits, makes it easy to represent super positions 0011 means it can be 2 or 1
        for (var r = 0; r < 9; ++r)
        {
            for (var c = 0; c < 9; ++c)
            {
                if (board[r, c] == 0)
                    board[r, c] = AllSuperPositionsMask;
                else
                    board[r, c] = (1 << (board[r, c] - 1)) | UncollapsedMask;
            }
        }

        if (!Solve()) return false;

        // Convert bit index back to value
        for (var r = 0; r < 9; ++r)
        {
            for (var c = 0; c < 9; ++c)
            {
                board[r, c] = HighestSetBitIndex(board[r, c]);
            }
        }
        return true;


        bool Solve()
        {
            if (!LowestEntropyCel(board, out int r, out int c)) 
                return true;

            var neighbors = Neighbors(r, c);

            var originalValue = board[r, c];
            var bitMasks = EachBit(UnsetBits(board[r, c], UncollapsedMask));
            foreach (var mask in bitMasks)
            {
                board[r, c] = mask;

                foreach (var (nr, nc) in neighbors)
                    board[nr, nc] = UnsetBits(board[nr, nc], mask);

                if (Solve()) return true;

                foreach (var (nr, nc) in neighbors)
                    board[nr, nc] |= mask;
            }

            board[r, c] = originalValue;
            return false;
        }
    }

    private int HighestSetBitIndex(int num)
    {
        int count = 0;
        while(num > 0)
        {
            count++;
            num >>= 1;
        }
        return count;
    }

    private IEnumerable<int> EachBit(int num)
    {
        int count = 1;
        while (num > 0)
        {
            if ((num & 1) == 1)
                yield return count;
            count <<= 1;
            num >>= 1;
        }
        yield break;
    }

    public static int CountSetBits(int n)
    {
        int count = 0;
        while (n != 0)
        {
            n &= (n - 1);
            count++;
        }
        return count;
    }

    private int UnsetBits(int num, int mask)
    {
        return num ^ (num & mask);
    }

    private bool AreBitsSet(int num, int mask)
    {
        return (num & mask) == mask;
    }

    private bool LowestEntropyCel(int[,] board, out int r, out int c)
    {
        int minEntropy = int.MaxValue;
        r = -1;
        c = -1;
        for (var rr = 0; rr < 9; ++rr)
        {
            for (var cc = 0; cc < 9; ++cc)
            {
                if (!AreBitsSet(board[rr, cc], UncollapsedMask)) continue;
                var entropy = CountSetBits(board[rr, cc]);
                if (entropy < minEntropy)
                {
                    minEntropy = entropy;
                    r = rr;
                    c= cc;
                }
            }
        }
        return minEntropy != int.MaxValue;
    }

    // Will return dupes
    private IEnumerable<(int,int)> Neighbors(int r, int c)
    {
        for (var rr = 0; rr < 9; ++rr)
        {
            if (rr == r) continue;
            yield return (rr, c);
        }

        for (var cc = 0; cc < 9; ++cc)
        {
            if (cc == c) continue;
            yield return (r, cc);
        }

        for (var i = 0; i < 9; ++i)
        {
            var cc = ((c / 3) * 3) + (i % 3);
            var rr = ((r / 3) * 3) + (i / 3);
            if (rr == r && cc == c) continue;
            yield return (rr, cc);
        }
    }

    private bool BasicValidate(int[,] board)
    {
        if (board.GetLength(0) != 9 || board.GetLength(1) != 9)
            return false;

        for (var r = 0; r < 9; ++r)
        {
            for (var c = 0; c < 9; ++c)
            {
                if (0 > board[r, c] && board[r, c] > 9)
                    return false;
            }
        }

        // TODO row col and square validation

        return true;
    }
}