using AF_1cosmosdb.models;
using Microsoft.WindowsAzure.Storage.Table;
using System;
using System.Collections.Generic;
using System.Text;

namespace AF_1cosmosdb
{
    class DhtMessage : TableEntity, ISortable
    {
        public string ID { get; set; }
        public double temperature { get; set; }
        public double humidity { get; set; }
        public long messageCreated { get; set; }
    }
}
