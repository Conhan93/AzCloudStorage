using System;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Extensions.Http;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Logging;
using Microsoft.Azure.Documents.Client;
using System.Linq;
using System.Collections.Generic;

namespace AF_1cosmosdb
{
    public static class GetFromCosmos
    {
        [FunctionName("GetFromCosmos")]
        public static async Task<IActionResult> Run(
                [HttpTrigger(AuthorizationLevel.Anonymous, "get", Route = null)] HttpRequest req,
                [CosmosDB(
            databaseName:"con-cosmos",
            collectionName:"Messages",
            ConnectionStringSetting = "CosmosConnection"
            )] DocumentClient cosmosdb,
                ILogger log)
        {
            Uri collectionUri = UriFactory.CreateDocumentCollectionUri("con-cosmos", "Messages");

            string[] types = { "humidity", "Volt", "luminosity" };
            string condition = "";

            // check for keys
            foreach (var type in types)
                if (req.Query.ContainsKey(type))
                    condition = type;

            // create and execute documentquery
            IEnumerable<dynamic> query = cosmosdb.CreateDocumentQuery<dynamic>(collectionUri, "SELECT TOP 10 * " +
                " FROM c" +
                $" WHERE  c.{condition} >= 0" +
                " ORDER BY c.messageCreated DESC")
                .AsEnumerable<dynamic>();

            return new OkObjectResult(query);
        }

    }
}
