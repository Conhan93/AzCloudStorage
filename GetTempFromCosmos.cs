using System;
using System.IO;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Extensions.Http;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Logging;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace AF_1cosmosdb
{
    public static class GetTempFromCosmos
    {
        [FunctionName("GetTempFromCosmos")]
        public static IActionResult Run(
            [HttpTrigger(AuthorizationLevel.Function, "get", Route = null)] HttpRequest req,
            [CosmosDB(
            databaseName:"con-cosmos",
            collectionName:"Messages",
            ConnectionStringSetting = "CosmosConnection",
            CreateIfNotExists = true,
            SqlQuery = "SELECT TOP 10 *" +
            " FROM c" +
            " WHERE c.humidity >= 0" +
            " ORDER BY c.messageCreated DESC"
            )] IEnumerable<dynamic> cosmosdb,
            ILogger log)
        {
            log.LogInformation("C# HTTP trigger function processed a request.");
            
            if (req.Query.ContainsKey("dht"))
                log.LogInformation("body contains dht");
            if(cosmosdb == null)
            {
                log.LogInformation("unable to find entries");
                return new NotFoundResult();
            }
            log.LogInformation("items found");
            return new OkObjectResult(cosmosdb);
        }
    }
}
