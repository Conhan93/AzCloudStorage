

let tabledata = document.getElementById("tabledata");

let dhtButton = document.getElementById("dht");
let voltButton = document.getElementById("volt");
let lumButton = document.getElementById("lum");

let storageButton = document.getElementById('storage');

let headers = document.getElementById('header');

dhtButton.addEventListener('click',getDHT);
voltButton.addEventListener('click',getVolt);
lumButton.addEventListener('click',getLum);
storageButton.addEventListener('click',changeStorage);

var FunctionAppName = "ENTER YOUR FUNCTION APP NAME";

function changeStorage()
{
    if(storageButton.innerHTML == 'cosmos')
        storageButton.innerHTML = 'table';
    else
        storageButton.innerHTML = 'cosmos';
}
function getDHT()
{
    headers.innerHTML = `
    <tr>
    <th scope="col">Device ID</th>
    <th scope="col">Temperature</th>
    <th scope="col">Humidity</th>
    <th scope="col">Timestamp</th>
    </tr>`;

    tabledata.innerHTML = "";
    if(storageButton.innerHTML == 'cosmos')
    {
        fetch(`https://${FunctionAppName}.azurewebsites.net/api/GetFromCosmos?humidity`)
        .then(response => response.json())
        .then(data => {
            console.log(data)
            for(let row of data)
            {
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
            console.log(data);
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
function getVolt()
{

    headers.innerHTML = `
    <tr>
    <th scope="col">Device ID</th>
    <th scope="col">Volt</th>
    <th scope="col">Timestamp</th>
    </tr>`;
    tabledata.innerHTML = "";
    if(storageButton.innerHTML == 'cosmos')
        fetch(`https://${FunctionAppName}.azurewebsites.net/api/GetFromCosmos?volt`).
        then(response => response.json())
            .then(data => {
            console.log(data)
            for(let row of data)
            {
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
            console.log(data)
            for(let row of data)
            {
                tabledata.innerHTML += `<tr>
                                        <td>${row.id}</td>
                                        <td>${row.volt.toFixed(2)}</td>
                                        <td>${toIso(row.messageCreated)}</td>`
            }
        })
}
function getLum()
{
    headers.innerHTML = `
    <tr>
    <th scope="col">Device ID</th>
    <th scope="col">Luminosity</th>
    <th scope="col">Timestamp</th>
    </tr>`;
    tabledata.innerHTML = "";
    if(storageButton.innerHTML == 'cosmos')
        fetch(`https://${FunctionAppName}.azurewebsites.net/api/GetFromCosmos?luminosity`).
        then(response => response.json())
            .then(data => {
            console.log(data)
            for(let row of data)
            {
                tabledata.innerHTML += `<tr>
                <td>${row.ID}</td>
                <td>${row.luminosity.toFixed(2)}%</td>
                <td>${toIso(row.messageCreated)}</td>`
            }
        })
    else
        fetch(`https://${FunctionAppName}.azurewebsites.net/api/GetTable?lum`).
        then(response => response.json())
            .then(data => {
            console.log(data)
            for(let row of data)
            {
                tabledata.innerHTML += `<tr>
                <td>${row.id}</td>
                <td>${row.luminosity.toFixed(2)}%</td>
                <td>${toIso(row.messageCreated)}</td>`
            }
        })
}
function toIso(timestamp)
{
    var datetime = new Date(timestamp * 1000);
    return datetime.toUTCString();
}
