function toggleWindow(windowId) {
    var status = document.getElementById('status' + windowId.slice(-1));
    var checkbox = document.querySelector(`#${windowId} .switch input`);

    if (checkbox.checked) {
        status.textContent = "On";
    } else {
        status.textContent = "Off";
    }
}

// Sample function to update values
function updateValues() {
    document.getElementById('temperatureValue').textContent = '28°C';
    document.getElementById('waterLevelValue').textContent = '60%';
    document.getElementById('soilMoistureValue').textContent = '45%';
}

// Call this function to update the values dynamically when needed
updateValues();


// Function to fetch sensor data from the ESP32
function fetchSensorData() {
    fetch('/data')
    .then(response => response.json())
    .then(data => {
        document.getElementById('temperatureValue').textContent = data.temperature + '°C';
        document.getElementById('waterLevelValue').textContent = '60%'; // Update with actual sensor data if available
        document.getElementById('soilMoistureValue').textContent = '45%'; // Update with actual sensor data if available
    })
    .catch(error => console.error('Error fetching sensor data:', error));
}

// Call this function every 2 seconds to update the values
setInterval(fetchSensorData, 2000);
