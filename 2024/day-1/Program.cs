// See https://aka.ms/new-console-template for more information
Console.WriteLine("Hello, World!");

var lines = File.ReadLines("input.txt").ToList();

List<int> listA = [];
List<int> listB = [];

foreach (var line in lines)
{
    Console.WriteLine($"reading line {line}");
    var values = line.Split("   ");
    Console.WriteLine($"parsing values {values}");
    listA.Add(int.Parse(values[0].Trim()));
    listB.Add(int.Parse(values[1].Trim()));
}

listA.Sort();
listB.Sort();

var sum = 0;

for (int i = 0; i < listA.Count; i++)
{
    Console.WriteLine($"adding {listB[i]} minus {listA[i]}");
    sum += Math.Abs(listB[i] - listA[i]);
}

Console.WriteLine($"And the sum is: {sum}");
