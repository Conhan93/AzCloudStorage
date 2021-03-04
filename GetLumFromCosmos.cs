using System;
using System.IO;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Extensions.Http;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json;
using System.Collections.Generic;

namespace AF_1cosmosdb
{
    public static class GetLumFromCosmos
    {
        [FunctionName("GetLumFromCosmos")]
        public static async Task<IActionResult> Run(
          [HttpTrigger(AuthorizationLevel.Function, "get", Route = null)] HttpRequest req,
            [CosmosDB(
            databaseName:"con-cosmos",
            collectionName:"Messages",
            ConnectionStringSetting = "CosmosConnection",
            CreateIfNotExists = true,
            SqlQuery = "SELECT TOP 10 *" +
            " FROM c" +
            " WHERE  c.luminosity >= 0" +
            " ORDER BY c.messageCreated DESC"
            )] IEnumerable<dynamic> cosmosdb,
            ILogger log)
        {

            if (cosmosdb == null)
            {
                log.LogInformation("unable to find entries");
                return new NotFoundResult();
            }
            return new OkObjectResult(cosmosdb);
        }
    }
}
