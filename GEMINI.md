# httpcpp

This project is a simple C++ HTTP client library.

## Features

- Make GET requests to a given URL.
- Parse HTTP responses, including status code, headers, and body.

## Components

- `HttpClient`: The main class for making HTTP requests.
- `HttpResponse`: Represents the HTTP response from the server.
- `HttpResponseParser`: Parses a raw HTTP response string into an `HttpResponse` object.
- `Socket`: A wrapper for socket operations.

## Example Usage

The `main.cpp` file provides an example of how to use the library to make a GET request to "http://www.google.com" and print the response.
