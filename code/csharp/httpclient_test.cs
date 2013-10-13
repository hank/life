using System;
using System.Net;
class MainClass
{
    public static void Main(String[] args)
    {
        if(args.Length == 0)
        {
            Console.WriteLine("Requires some stock tickers");
            return;
        }
        new Client().Get(args);
    }
}

public class Client
{
    public void Get(String[] args)
    {
        string stocks = "";
        for(int i=0; i < args.Length; ++i)
        {
            stocks += args[i];
            if(i != args.Length - 1) stocks += ",";
        }
        //Console.WriteLine("Getting " + stocks);
        WebClient httpClient = new WebClient();
        string response = httpClient.DownloadString("http://download.finance.yahoo.com/d/quotes.csv?s="+stocks+"&f=nsl1op&e=.csv");
        Console.WriteLine(response);
    }
}


