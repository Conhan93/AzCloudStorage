using Microsoft.WindowsAzure.Storage.Table;
using System;
using System.Collections.Generic;
using System.Text;

namespace AF_1cosmosdb.models
{
    class VoltMessage : TableEntity, ISortable
    {
        public string ID { get; set; }
        public double volt { get; set; }
        public long messageCreated { get; set; }
    }
}
