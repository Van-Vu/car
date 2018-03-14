using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Threading;
using HtmlAgilityPack;
using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;
using Xunit;

namespace SeleniumScrape
{
    public class SetForLife
    {
        [Fact]
        public void GrabMonthlyResult()
        {
            var yearValue = "2017";
            var monthValue = "June";


            using (var driver = new ChromeDriver(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location)))
            {
                driver.Navigate().GoToUrl(@"https://thelott.com/set-for-life/results");
                Thread.Sleep(TimeSpan.FromMilliseconds(500));
                var year = driver.FindElement(By.ClassName("select-year"));
                year.Click();
                var yearOption = driver.FindElement(By.XPath($"//option[@class='au-target'][text()='{yearValue}']"));
                yearOption.Click();
                var month = driver.FindElement(By.ClassName("select-month"));
                month.Click();
                var monthOption = driver.FindElement(By.XPath($"//option[@class='au-target'][text()='{monthValue}']"));
                monthOption.Click();
                var clickButton = driver.FindElement(By.ClassName("button-find"));
                clickButton.Click();

                Thread.Sleep(TimeSpan.FromMilliseconds(500));

                var doc = new HtmlDocument();
                doc.LoadHtml(driver.PageSource);

                var values = doc.DocumentNode
                            .SelectNodes("//lotto-numbers/div/div[@class='number-container']/div[@class='number']");

                var drawLines = values.Select(number => Convert.ToInt16(number.InnerText)).Select(dummy => (int) dummy).ToList();

                var result = SplitList(drawLines, 8);
                result.Reverse();

                using (var file = File.CreateText($"{yearValue}{monthValue}.csv"))
                {
                    foreach (var arr in result)
                    {
                        file.WriteLine(string.Join(",", arr));
                    }
                }
            }
        }

        public List<List<int>> SplitList(List<int> list, int size = 50)
        {
            var result = new List<List<int>>();
            for (int i = 0; i < list.Count; i += size)
                result.Add(list.GetRange(i, Math.Min(size, list.Count - i)));
            return result;
        }
    }
}