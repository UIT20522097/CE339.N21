/*
    *  This file contains the database connection information.
    *  It is used to connect to the database with REST API.
    *  All the connection using GET method.
*/

// Write a Channel Field
var writeChannelField = (field, value) => {
    /*
        *  The field is the field number of the channel.
        *  The value is the value that you want to write.
    */
    const url = `https://api.thingspeak.com/update?api_key=Z2AZ4DRNPIPWMCK6&field${field}=${value}`;
    return url;
}

// Read a Channel Field
var readChannelField = (field, numbers) => {
    /*
        *  The field is the field number of the channel.
        *  The numbers is the number of data that you want to read.
    */
    const url = `https://api.thingspeak.com/channels/2188986/fields/${field}.json?api_key=M79QI9F8V63EPJ35&results=${numbers}`;
    return url;
}