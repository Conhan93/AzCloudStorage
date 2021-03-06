using Microsoft.WindowsAzure.Storage.Table;

namespace AF_1cosmosdb.models
{
    class LuminosityMessage : TableEntity, ISortable
    {
        public string ID { get; set; }
        public double luminosity { get; set; }
        public long messageCreated { get; set; }
    }
}
