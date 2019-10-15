using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Net.Http;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using C_Sharp_Challenge_Skeleton.Answers;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json;

namespace C_Sharp_Skeleton_2019.Tests
{
    [TestClass]
    public class SkeletonTests
    {
        private static readonly HttpClient client = new HttpClient();
        private readonly string baseUrl = "https://cscc-gl.herokuapp.com/";

        [TestMethod]
        public async Task TestQ1()
        {
            var travisUUID = Environment.GetEnvironmentVariable("travistestidentifier");
            if (travisUUID == null)
            {
                travisUUID = "";
            }
            Console.WriteLine("Testing Q1");
            string responseBody = await client.GetStringAsync(baseUrl + "tests/run/1/" + travisUUID);
            List<TestCase> testCases = JsonConvert.DeserializeObject<List<TestCase>>(responseBody);
            List<Answer> answers = new List<Answer>();

            foreach (var test in testCases)
            {
                try
                {
                    Answer answer = new Answer();
                    Q1Object input = JsonConvert.DeserializeObject<Q1Object>(test.input);
                    var cancellationToken = new CancellationTokenSource();
                    cancellationToken.CancelAfter(1000);
                    await Task.Run(() => answer = getFirstAnswer(input, test), cancellationToken.Token);
                    answers.Add(answer);
                }
                catch (TaskCanceledException _)
                {
                    Console.WriteLine("A test in Question 1 has timed out. Tests must complete within one second.");
                    answers.Add(new Answer()
                    {
                        questionNumber = 1,
                        testNumber = test.testNumber,
                        correct = "TIMED_OUT",
                        speed = -1
                    });
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.StackTrace);
                }
            }

            if (travisUUID.Length > 0)
            {
                Console.WriteLine("Submitting Q1");
                string ans = JsonConvert.SerializeObject(answers);
                await client.PostAsync(baseUrl + "answer/contestant/" + travisUUID + "/1", new StringContent(ans, Encoding.UTF8, "application/json"));
            }
        }

        Answer getFirstAnswer(Q1Object input, TestCase test)
        {
            var timer = new Stopwatch();

            timer.Start();

            var answer = Question1.Answer(input.initialLevelOfDebt, input.interestPercentage, input.repaymentPercentage);

            timer.Stop();

            var timeTaken = ((double)timer.ElapsedTicks / Stopwatch.Frequency) * 1000000000;

            return new Answer()
            {
                questionNumber = 1,
                testNumber = test.testNumber,
                correct = answer == test.output ? "CORRECT" : "INCORRECT",
                speed = timeTaken
            };
        }

        [TestMethod]
        public async Task TestQ2()
        {
            var travisUUID = Environment.GetEnvironmentVariable("travistestidentifier");
            if (travisUUID == null)
            {
                travisUUID = "";
            }
            Console.WriteLine("Testing Q2");
            string responseBody = await client.GetStringAsync(baseUrl + "tests/run/2/" + travisUUID);
            List<TestCase> testCases = JsonConvert.DeserializeObject<List<TestCase>>(responseBody);
            List<Answer> answers = new List<Answer>();

            foreach (var test in testCases)
            {
                try
                {
                    Answer answer = new Answer();
                    Q2Object input = JsonConvert.DeserializeObject<Q2Object>(test.input);
                    var cancellationToken = new CancellationTokenSource();
                    cancellationToken.CancelAfter(1000);
                    await Task.Run(() => answer = getSecondAnswer(input, test), cancellationToken.Token);
                    answers.Add(answer);
                }
                catch (TaskCanceledException _)
                {
                    Console.WriteLine("A test in Question 2 has timed out. Tests must complete within one second.");
                    answers.Add(new Answer()
                    {
                        questionNumber = 2,
                        testNumber = test.testNumber,
                        correct = "TIMED_OUT",
                        speed = -1
                    });
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.StackTrace);
                }
            }

            if (travisUUID.Length > 0)
            {
                Console.WriteLine("Submitting Q2");
                string ans = JsonConvert.SerializeObject(answers);
                await client.PostAsync(baseUrl + "answer/contestant/" + travisUUID + "/2", new StringContent(ans, Encoding.UTF8, "application/json"));
            }
        }

        Answer getSecondAnswer(Q2Object input, TestCase test)
        {
            var timer = new Stopwatch();

            timer.Start();

            var answer = Question2.Answer(input.risk, input.bonus, input.trader);

            timer.Stop();

            var timeTaken = ((double)timer.ElapsedTicks / Stopwatch.Frequency) * 1000000000;

            return new Answer()
            {
                questionNumber = 2,
                testNumber = test.testNumber,
                correct = answer == test.output ? "CORRECT" : "INCORRECT",
                speed = timeTaken
            };
        }

        [TestMethod]
        public async Task TestQ3()
        {
            var travisUUID = Environment.GetEnvironmentVariable("travistestidentifier");
            if (travisUUID == null)
            {
                travisUUID = "";
            }
            Console.WriteLine("Testing Q3");
            string responseBody = await client.GetStringAsync(baseUrl + "tests/run/3/" + travisUUID);
            List<TestCase> testCases = JsonConvert.DeserializeObject<List<TestCase>>(responseBody);
            List<Answer> answers = new List<Answer>();

            foreach (var test in testCases)
            {
                try
                {
                    Answer answer = new Answer();
                    Q3Object input = JsonConvert.DeserializeObject<Q3Object>(test.input);
                    var cancellationToken = new CancellationTokenSource();
                    cancellationToken.CancelAfter(1000);
                    await Task.Run(() => answer = getThirdAnswer(input, test), cancellationToken.Token);
                    answers.Add(answer);
                }
                catch (TaskCanceledException _)
                {
                    Console.WriteLine("A test in Question 3 has timed out. Tests must complete within one second.");
                    answers.Add(new Answer()
                    {
                        questionNumber = 3,
                        testNumber = test.testNumber,
                        correct = "TIMED_OUT",
                        speed = -1
                    });
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.StackTrace);
                }
            }

            if (travisUUID.Length > 0)
            {
                Console.WriteLine("Submitting Q3");
                string ans = JsonConvert.SerializeObject(answers);
                await client.PostAsync(baseUrl + "answer/contestant/" + travisUUID + "/3", new StringContent(ans, Encoding.UTF8, "application/json"));
            }
        }

        Answer getThirdAnswer(Q3Object input, TestCase test)
        {
            var timer = new Stopwatch();

            timer.Start();

            var answer = Question3.Answer(input.scores, input.alice);

            timer.Stop();

            var timeTaken = ((double)timer.ElapsedTicks / Stopwatch.Frequency) * 1000000000;

            return new Answer()
            {
                questionNumber = 3,
                testNumber = test.testNumber,
                correct = answer == test.output ? "CORRECT" : "INCORRECT",
                speed = timeTaken
            };
        }

        [TestMethod]
        public async Task TestQ4()
        {
            var travisUUID = Environment.GetEnvironmentVariable("travistestidentifier");
            if (travisUUID == null)
            {
                travisUUID = "";
            }
            Console.WriteLine("Testing Q4");
            string responseBody = await client.GetStringAsync(baseUrl + "tests/run/4/" + travisUUID);
            List<TestCase> testCases = JsonConvert.DeserializeObject<List<TestCase>>(responseBody);
            List<Answer> answers = new List<Answer>();

            foreach (var test in testCases)
            {
                try
                {
                    Answer answer = new Answer();
                    Q4Object input = JsonConvert.DeserializeObject<Q4Object>(test.input);
                    var cancellationToken = new CancellationTokenSource();
                    cancellationToken.CancelAfter(1000);
                    await Task.Run(() => answer = getFourthAnswer(input, test), cancellationToken.Token);
                    answers.Add(answer);
                }
                catch (TaskCanceledException _)
                {
                    Console.WriteLine("A test in Question 4 has timed out. Tests must complete within one second.");
                    answers.Add(new Answer()
                    {
                        questionNumber = 4,
                        testNumber = test.testNumber,
                        correct = "TIMED_OUT",
                        speed = -1
                    });
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.StackTrace);
                }
            }

            if (travisUUID.Length > 0)
            {
                Console.WriteLine("Submitting Q4");
                string ans = JsonConvert.SerializeObject(answers);
                await client.PostAsync(baseUrl + "answer/contestant/" + travisUUID + "/4", new StringContent(ans, Encoding.UTF8, "application/json"));
            }
        }

        Answer getFourthAnswer(Q4Object input, TestCase test)
        {
            var timer = new Stopwatch();

            timer.Start();

            var answer = Question4.Answer(input.v, input.c, input.mc);

            timer.Stop();

            var timeTaken = ((double)timer.ElapsedTicks / Stopwatch.Frequency) * 1000000000;

            return new Answer()
            {
                questionNumber = 4,
                testNumber = test.testNumber,
                correct = answer == test.output ? "CORRECT" : "INCORRECT",
                speed = timeTaken
            };
        }

        [TestMethod]
        public async Task TestQ5()
        {
            var travisUUID = Environment.GetEnvironmentVariable("travistestidentifier");
            if (travisUUID == null)
            {
                travisUUID = "";
            }
            Console.WriteLine("Testing Q5");
            string responseBody = await client.GetStringAsync(baseUrl + "tests/run/5/" + travisUUID);
            List<TestCase> testCases = JsonConvert.DeserializeObject<List<TestCase>>(responseBody);
            List<Answer> answers = new List<Answer>();

            foreach (var test in testCases)
            {
                try
                {
                    Answer answer = new Answer();
                    int[] input = JsonConvert.DeserializeObject<int[]>(test.input);
                    var cancellationToken = new CancellationTokenSource();
                    cancellationToken.CancelAfter(1000);
                    await Task.Run(() => answer = getFifthAnswer(input, test), cancellationToken.Token);
                    answers.Add(answer);
                }
                catch (TaskCanceledException _)
                {
                    Console.WriteLine("A test in Question 5 has timed out. Tests must complete within one second.");
                    answers.Add(new Answer()
                    {
                        questionNumber = 5,
                        testNumber = test.testNumber,
                        correct = "TIMED_OUT",
                        speed = -1
                    });
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.StackTrace);
                }
            }


            if (travisUUID.Length > 0)
            {
                Console.WriteLine("Submitting Q5");
                string ans = JsonConvert.SerializeObject(answers);
                await client.PostAsync(baseUrl + "answer/contestant/" + travisUUID + "/5", new StringContent(ans, Encoding.UTF8, "application/json"));
            }
        }

        Answer getFifthAnswer(int[] input, TestCase test)
        {
            var timer = new Stopwatch();

            timer.Start();

            var answer = Question5.Answer(input);

            timer.Stop();

            var timeTaken = ((double)timer.ElapsedTicks / Stopwatch.Frequency) * 1000000000;

            return new Answer()
            {
                questionNumber = 5,
                testNumber = test.testNumber,
                correct = answer == test.output ? "CORRECT" : "INCORRECT",
                speed = timeTaken
            };
        }

        [TestMethod]
        public async Task TestQ6()
        {
            var travisUUID = Environment.GetEnvironmentVariable("travistestidentifier");
            if (travisUUID == null)
            {
                travisUUID = "";
            }
            Console.WriteLine("Testing Q6");
            string responseBody = await client.GetStringAsync(baseUrl + "tests/run/6/" + travisUUID);
            List<TestCase> testCases = JsonConvert.DeserializeObject<List<TestCase>>(responseBody);
            List<Answer> answers = new List<Answer>();

            foreach (var test in testCases)
            {
                try
                {
                    Answer answer = new Answer();
                    string[] input = JsonConvert.DeserializeObject<string[]>(test.input);
                    var cancellationToken = new CancellationTokenSource();
                    cancellationToken.CancelAfter(1000);
                    await Task.Run(() => answer = getSixthAnswer(input, test), cancellationToken.Token);
                    answers.Add(answer);
                }
                catch (TaskCanceledException _)
                {
                    Console.WriteLine("A test in Question 6 has timed out. Tests must complete within one second.");
                    answers.Add(new Answer()
                    {
                        questionNumber = 6,
                        testNumber = test.testNumber,
                        correct = "TIMED_OUT",
                        speed = -1
                    });
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.StackTrace);
                }
            }

            if (travisUUID.Length > 0)
            {
                Console.WriteLine("Submitting Q6");
                string ans = JsonConvert.SerializeObject(answers);
                await client.PostAsync(baseUrl + "answer/contestant/" + travisUUID + "/6", new StringContent(ans, Encoding.UTF8, "application/json"));
            }
        }

        Answer getSixthAnswer(string[] input, TestCase test)
        {
            var timer = new Stopwatch();

            timer.Start();

            var answer = Question6.Answer(input);

            timer.Stop();

            var timeTaken = ((double)timer.ElapsedTicks / Stopwatch.Frequency) * 1000000000;

            return new Answer()
            {
                questionNumber = 6,
                testNumber = test.testNumber,
                correct = answer == test.output ? "CORRECT" : "INCORRECT",
                speed = timeTaken
            };
        }

        private class TestCase
        {
            public int testNumber { get; set; }
            public string input { get; set; }
            public int output { get; set; }
        }

        private class TestCaseList
        {
            public List<TestCase> testCases { get; set; }
        }

        private class Answer
        {
            public int questionNumber { get; set; }
            public int testNumber { get; set; }
            public string correct { get; set; }
            public double speed { get; set; }
        }

        private class Q1Object
        {
            public double initialLevelOfDebt { get; set; }
            public double interestPercentage { get; set; }
            public double repaymentPercentage { get; set; }
        }

        private class Q2Object
        {
            public int[] risk { get; set; }
            public int[] bonus { get; set; }
            public int[] trader { get; set; }
        }

        private class Q3Object
        {
            public int[] scores { get; set; }
            public int[] alice { get; set; }
        }

        private class Q4Object
        {
            public int[] v { get; set; }
            public int[] c { get; set; }
            public int mc { get; set; }
        }
    }
}
