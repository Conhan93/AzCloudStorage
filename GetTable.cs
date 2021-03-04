using System;
using System.IO;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Extensions.Http;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json;
using Microsoft.WindowsAzure.Storage.Table;
using System.Collections.Generic;
using AF_1cosmosdb.models;
using System.Linq;

namespace AF_1cosmosdb
{
    public static class GetTable
    {
        [FunctionName("GetTableLum")]
        public static async Task<IActionResult> Run(
            [HttpTrigger(AuthorizationLevel.Function, "get", Route = null)] HttpRequest req,
            [Table("Messages")] CloudTable cloudtable,
            ILogger log)
        {
            if(req.Query.ContainsKey("lum"))
            {
                IEnumerable<LuminosityMessage> results = await cloudtable
                 .ExecuteQuerySegmentedAsync(new TableQuery<LuminosityMessage>(), null);
                

                results = results.Where(ts => ts.PartitionKey == "luminosity");
                results = results.OrderByDescending(ts => ts.messageCreated);
                results = results.Take(10);

                return results != null ?
                    (ActionResult)new OkObjectResult(results) :
                    new BadRequestObjectResult("[]");
            }
            else if(req.Query.ContainsKey("dht"))
            {
                IEnumerable<DhtMessage> results = await cloudtable
                 .ExecuteQuerySegmentedAsync(new TableQuery<DhtMessage>(), null);

                results = results.Where(ts => ts.PartitionKey == "dht");
                results = results.OrderByDescending(ts => ts.messageCreated);
                results = results.Take(10);

                return results != null ?
                    (ActionResult)new OkObjectResult(results) :
                    new BadRequestObjectResult("[]");
            }
            else if(req.Query.ContainsKey("volt"))
            {
                IEnumerable<VoltMessage> results = await cloudtable
                 .ExecuteQuerySegmentedAsync(new TableQuery<VoltMessage>(), null);

                results = results.Where(ts => ts.volt >= 0);
                results = results.OrderByDescending(ts => ts.PartitionKey == "volt");
                results = results.Take(10);

                return results != null ?
                    (ActionResult)new OkObjectResult(results) :
                    new BadRequestObjectResult("[]");
            }

            return new BadRequestObjectResult("[]");
            
        }
    }
}
