#include "httpcpp/HttpClient.hpp"
#include "httpcpp/HttpResponse.hpp"
#include "httpcpp/Socket.hpp"
#include <exception>
#include <iostream>
#include <string_view>

int main()
{
    try
    {
        httpcpp::Socket socket;
        httpcpp::HttpClient client(&socket);
        constexpr std::string_view body {R"(
from(bucket: "fve")
  |> range(start: -1m, stop: now())
  |> filter(fn: (r) => r["_measurement"] == "realtime")
  |> filter(fn: (r) => r["_field"] == "Batpower_Charge1" or
                       r["_field"] == "Battery_Capacity" or
                       r["_field"] == "feedin_power" or
                       r["_field"] == "GridPower" or
                       r["_field"] == "FeedinPower_Tphase" or
                       r["_field"] == "FeedinPower_Sphase" or
                       r["_field"] == "FeedinPower_Rphase" or
                       r["_field"] == "GridPower_T" or
                       r["_field"] == "GridPower_S" or
                       r["_field"] == "GridPower_R")
  |> mean()
  |> pivot(rowKey: ["_stop"], columnKey: ["_field"], valueColumn: "_value")
  |> map(fn: (r) => ({r with time: uint(v: r._stop) / uint(v: 1000000000)}))
  |> drop(columns: ["_start", "_stop", "_measurement"])
)"};
        httpcpp::HttpResponse const response = client.post(
            "http://fve.local:8086/api/v2/query?org=doma", std::string(body),
            {
                {"Authorization", "Token my-super-secret-auth-token"},
                { "Content-Type",             "application/vnd.flux"},
                {       "Accept",                  "application/csv"}
        });

        std::cout << "Status Code: " << response.getStatusCode() << '\n';
        std::cout << "Headers:" << '\n';
        for (const auto& header : response.getHeaders()) {
            std::cout << "  " << header.first << ": " << header.second << '\n';
        }
        std::cout << "Body:" << '\n';
        std::cout << response.getBody() << '\n';
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
