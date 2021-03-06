using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Extensions.Http;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Logging;
using Microsoft.WindowsAzure.Storage.Table;
using System.Collections.Generic;
using AF_1cosmosdb.models;
using System.Linq;


namespace AF_1cosmosdb
{
    public static class GetTable
    {
        [FunctionName("GetTable")]
        public static async Task<IActionResult> Run(
            [HttpTrigger(AuthorizationLevel.Anonymous, "get", Route = null)] HttpRequest req,
            [Table("Messages")] CloudTable cloudtable,
            ILogger log)
        {
            // sensor types
            string[] types = { "dht", "volt", "luminosity" };
            string type = "";

            // check query keys
            foreach (var _type in types)
                if (req.Query.ContainsKey(_type))
                    type = _type;

            // return collection
            IEnumerable<dynamic> results;

            switch(type)
            {
                case "luminosity":
                    results = await GetItemsAsync<LuminosityMessage>(cloudtable, type);
                    results = results.OrderByDescending(ts => ts.messageCreated);
                    results = results.Take(10);

                    break;
                case "volt":
                    results = await GetItemsAsync<VoltMessage>(cloudtable, type);
                    results = results.OrderByDescending(ts => ts.messageCreated);
                    results = results.Take(10);

                    break;
                case "dht":
                    results = await GetItemsAsync<DhtMessage>(cloudtable, type);
                    results = results.OrderByDescending(ts => ts.messageCreated);
                    results = results.Take(10);

                    break;
                default:
                    results = null;
                    break;
            }

            return results != null ?
                        (ActionResult)new OkObjectResult(results) :
                        new BadRequestObjectResult("[]");

        }
        // gets items by partitionkey, returns enumerable
        private static async Task<IEnumerable<T>> GetItemsAsync<T>(CloudTable cloudtable, string type)
        where T : ITableEntity, new()
        {
            IEnumerable<T> results = await cloudtable
                 .ExecuteQuerySegmentedAsync(new TableQuery<T>(), null);


            results = results.Where(ts => ts.PartitionKey == type);

            return results;
        }
    }
}
