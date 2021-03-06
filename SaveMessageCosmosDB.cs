using IoTHubTrigger = Microsoft.Azure.WebJobs.EventHubTriggerAttribute;

using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Host;
using Microsoft.Azure.EventHubs;
using System.Text;
using System.Net.Http;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json;
using Microsoft.WindowsAzure.Storage.Table;
using System;
using AF_1cosmosdb.models;

namespace AF_1cosmosdb
{
    public static class SaveMessageCosmosDB
    {
        private static HttpClient client = new HttpClient();

        [FunctionName("SaveMessageCosmosDB")]
        [return: Table("Messages")]
        public static DynamicTableEntity Run(
            [IoTHubTrigger("messages/events", Connection = "IotHubConnection", ConsumerGroup = "$Default")] EventData message,
            [CosmosDB(
                databaseName: "con-cosmos",
                collectionName: "Messages",
                ConnectionStringSetting = "CosmosConnection",
                CreateIfNotExists = true
            )]out dynamic cosmos,
            ILogger log
        )
        {
            // for table storage
            var ent = new DynamicTableEntity();


            switch (message.Properties["type"])
            {
                case "dht":
                    DhtMessage dht = JsonConvert.DeserializeObject<DhtMessage>(Encoding.UTF8.GetString(message.Body.Array));

                    ent.Properties["ID"] = new EntityProperty(dht.ID);
                    ent.Properties["temperature"] = new EntityProperty(dht.temperature);
                    ent.Properties["humidity"] = new EntityProperty(dht.humidity);
                    ent.Properties["messageCreated"] = new EntityProperty(dht.messageCreated);
                    ent.PartitionKey = message.Properties["type"].ToString();
                    ent.RowKey = Guid.NewGuid().ToString();
                    break;
                case "volt":
                    VoltMessage volt = JsonConvert.DeserializeObject<VoltMessage>(Encoding.UTF8.GetString(message.Body.Array));

                    ent.Properties["ID"] = new EntityProperty(volt.ID);
                    ent.Properties["volt"] = new EntityProperty(volt.volt);
                    ent.Properties["messageCreated"] = new EntityProperty(volt.messageCreated);
                    ent.PartitionKey = message.Properties["type"].ToString();
                    ent.RowKey = Guid.NewGuid().ToString();
                    break;
                case "luminosity":
                    LuminosityMessage lum = JsonConvert.DeserializeObject<LuminosityMessage>(Encoding.UTF8.GetString(message.Body.Array));

                    ent.Properties["ID"] = new EntityProperty(lum.ID);
                    ent.Properties["luminosity"] = new EntityProperty(lum.luminosity);
                    ent.Properties["messageCreated"] = new EntityProperty(lum.messageCreated);
                    ent.PartitionKey = message.Properties["type"].ToString();
                    ent.RowKey = Guid.NewGuid().ToString();
                    break;
                default:
                    log.LogInformation("unknown type");
                    break;
            }



            cosmos = Encoding.UTF8.GetString(message.Body.Array);
            log.LogInformation($"message processed: {Encoding.UTF8.GetString(message.Body.Array)}");

            // for table storage
            return ent;
        }
    }
}
