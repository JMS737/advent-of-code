var inputs = LoadInput("../input.txt");

var diffScore = GetTotalDifference(inputs);
Console.WriteLine($"Total difference is: {diffScore}");

var similarityScore = GetSimilarityScore(inputs);
Console.WriteLine($"And the similarity score is: {similarityScore}");

(List<int> ListLeft, List<int> ListRight) LoadInput(string filename)
{

    var lines = File.ReadLines(filename).ToList();

    List<int> listA = [];
    List<int> listB = [];

    foreach (var line in lines)
    {
        // Console.WriteLine($"reading line {line}");
        var values = line.Split("   ");
        listA.Add(int.Parse(values[0].Trim()));
        listB.Add(int.Parse(values[1].Trim()));
    }

    return (listA, listB);
}

int GetTotalDifference((List<int> Left, List<int> Right) inputs)
{
    var listA = inputs.Left.Order().ToList();
    var listB = inputs.Right.Order().ToList();

    var sum = 0;

    for (int i = 0; i < listA.Count; i++)
    {
        // Console.WriteLine($"adding {listB[i]} minus {listA[i]}");
        sum += Math.Abs(listB[i] - listA[i]);
    }

    return sum;
}

int GetSimilarityScore((List<int> Left, List<int> Right) inputs)
{
    var counts = inputs.Right
        .GroupBy(i => i)
        .ToDictionary(i => i.Key, i => i.Count());

    var sum = 0;
    foreach (var item in inputs.Left)
    {
        if (!counts.TryGetValue(item, out var count))
        {
            count = 0;
        }

        // Console.WriteLine($"found {count} occurences of {item}");

        sum += item * count;
    }

    return sum;
}
