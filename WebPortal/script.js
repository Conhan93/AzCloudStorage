

let tabledata = document.getElementById("tabledata");

let dhtButton = document.getElementById("dht");
let voltButton = document.getElementById("volt");
let lumButton = document.getElementById("lum");

let storageButton = document.getElementById('storage');

let headers = document.getElementById('header');

// button objects
dhtButton.addEventListener('click',getDHT);
voltButton.addEventListener('click',getVolt);
lumButton.addEventListener('click',getLum);
storageButton.addEventListener('click',changeStorage);

// really important
var FunctionAppName = "ENTER YOUR FUNCTION APP NAME";
// 
// 

// changes which storage solution to request data from
function changeStorage()
{
    if(storageButton.innerHTML == 'cosmos')
        storageButton.innerHTML = 'table';
    else
        storageButton.innerHTML = 'cosmos';
}
// gets and displays DHT data
function getDHT()
{
    // create headers
    headers.innerHTML = `
    <tr>
    <th scope="col">Device ID</th>
    <th scope="col">Temperature</th>
    <th scope="col">Humidity</th>
    <th scope="col">Timestamp</th>
    </tr>`;
    // clear table
    tabledata.innerHTML = "";

    if(storageButton.innerHTML == 'cosmos')
    {
        fetch(`https://${FunctionAppName}.azurewebsites.net/api/GetFromCosmos?humidity`)
        .then(response => response.json())
        .then(data => {
            // create table
            for(let row of data)
            {
              // add row
              tabledata.innerHTML += `<tr>
                                      <td>${row.ID}</td>
                                      <td>${row.temperature.toFixed(2)}</td>
                                      <td>${row.humidity.toFixed(2)}</td>
                                      <td>${toIso(row.messageCreated)}</td>`
            }
        })
    }
    else
    fetch(`https://${FunctionAppName}.azurewebsites.net/api/GetTable?dht`,
        )
        .then(response => response.json())
        .then(data => {

            for(let row of data)
            {
            tabledata.innerHTML += `<tr>
                                    <td>${row.id}</td>
                                    <td>${row.temperature.toFixed(2)}</td>
                                    <td>${row.humidity.toFixed(2)}</td>
                                    <td>${toIso(row.messageCreated)}</td>`
            }
        })
}
// gets and displays volt type data
function getVolt()
{
    // create header row
    headers.innerHTML = `
    <tr>
    <th scope="col">Device ID</th>
    <th scope="col">Volt</th>
    <th scope="col">Timestamp</th>
    </tr>`;
    // clear table
    tabledata.innerHTML = "";

    if(storageButton.innerHTML == 'cosmos')
        fetch(`https://${FunctionAppName}.azurewebsites.net/api/GetFromCosmos?volt`).
        then(response => response.json())
            .then(data => {
            // creates table
            for(let row of data)
            {
                // create row
                tabledata.innerHTML += `<tr>
                                        <td>${row.ID}</td>
                                        <td>${row.Volt.toFixed(2)}</td>
                                        <td>${toIso(row.messageCreated)}</td>`
            }
        })
    else
        fetch(`https://${FunctionAppName}.azurewebsites.net/api/GetTable?volt`).
        then(response => response.json())
            .then(data => {

            for(let row of data)
            {
                tabledata.innerHTML += `<tr>
                                        <td>${row.id}</td>
                                        <td>${row.volt.toFixed(2)}</td>
                                        <td>${toIso(row.messageCreated)}</td>`
            }
        })
}
// gets and displays luminosity type data
function getLum()
{
    // creates header row
    headers.innerHTML = `
    <tr>
    <th scope="col">Device ID</th>
    <th scope="col">Luminosity</th>
    <th scope="col">Timestamp</th>
    </tr>`;
    // clears previous data
    tabledata.innerHTML = "";

    if(storageButton.innerHTML == 'cosmos')
        fetch(`https://${FunctionAppName}.azurewebsites.net/api/GetFromCosmos?luminosity`).
        then(response => response.json())
            .then(data => {

            for(let row of data)
            {
                // add new row
                tabledata.innerHTML += `<tr>
                <td>${row.ID}</td>
                <td>${row.luminosity.toFixed(2)}%</td>
                <td>${toIso(row.messageCreated)}</td>`
            }
        })
    else
        fetch(`https://${FunctionAppName}.azurewebsites.net/api/GetTable?luminosity`).
        then(response => response.json())
            .then(data => {

            for(let row of data)
            {
                tabledata.innerHTML += `<tr>
                <td>${row.id}</td>
                <td>${row.luminosity.toFixed(2)}%</td>
                <td>${toIso(row.messageCreated)}</td>`
            }
        })
}
// converts unix timestamp to readable string format
function toIso(timestamp)
{
    var datetime = new Date(timestamp * 1000);
    return datetime.toUTCString();
}
