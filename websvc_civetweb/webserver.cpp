#include <iostream>
#include "CivetServer.h"
#include "webserver.h"
#include "cJSON/cJSON.h"

std::string str_info("info");
std::string str_MC("MC");
std::string str_XYZ("XYZ");

std::string str_scan("scan");
std::string str_stop("stop");
std::string str_snap("snap");
std::string str_saveRef("saveRef");
std::string str_saveDark("saveDark");
std::string str_autoGain("autoGain");
std::string str_lampOn("lampOn");
std::string str_lampOff("lampOff");
std::string str_park("park");
std::string str_homeXYZ("homeXYZ");
std::string str_eject("eject");
std::string str_pickSensor("pickSensor");
std::string str_sample("sample");
std::string str_shakerOn("shakerOn");
std::string str_shakerOff("shakerOff");
std::string str_shaker("shaker_");
std::string str_setSampleTemp("setSampleTemp");
std::string str_setSpectTemp("setSpectTemp");


static int
SendJSON(struct mg_connection* conn, cJSON* json_obj)
{
	char* json_str = cJSON_PrintUnformatted(json_obj);
	size_t json_str_len = strlen(json_str);

	//Send HTTP message header//
	mg_send_http_ok(conn, "application/json; charset=utf-8", json_str_len);

	// Send HTTP message content //
	mg_write(conn, json_str, json_str_len);

	// Free string allocated by cJSON_Print* //
	cJSON_free(json_str);

	return (int)json_str_len;
}


bool ExperimentHandler::handleGet(CivetServer* server, struct mg_connection* conn)
{
    std::cout << "handling get request ...\n";
	cJSON* obj_return = cJSON_CreateObject();
    if (!obj_return) {
        /* insufficient memory? */
        mg_send_http_error(conn, 500, "Server error");
        return false;
    }

    const struct mg_request_info* req_info = mg_get_request_info(conn);
    std::string query;

    if (req_info == NULL) {
        std::cout << "An error occurs when get request info \n";
    }
    else if (req_info->query_string == NULL) {
        std::cout << "No query string in the url" << std::endl;
    }
    else {
        query = std::string(req_info->query_string);
        std::cout << "query is: " << query << std::endl;
        std::string delimiter = "=";
        size_t pos = query.find(delimiter);
        if (pos == std::string::npos) { // no delimiter found
            std::cout << "Wrong URL request format " << std::endl;
            cJSON_AddStringToObject(obj_return, "Error", "Wrong URL request format ");
        }
        else {
            std::string para = query.substr(0, pos);
            std::cout << "para is: " << para << std::endl;
            std::string val = query.erase(0, pos + delimiter.length());
            std::cout << "val is: " << val << std::endl;

            if (0 == str_info.compare(para)) { // get info request
                if (0 == str_MC.compare(val)) {
                    std::cout << "Get MC info" << std::endl;
                }else if (0 == str_XYZ.compare(val)) {
                    std::cout << "Get XYZ info" << std::endl;
                }

            }

        }



    }

    cJSON_AddNumberToObject(obj_return, "exp_status", 0);
    SendJSON(conn, obj_return);
    cJSON_Delete(obj_return);

    return true;
}

bool ExperimentHandler::handlePost(CivetServer* server, struct mg_connection* conn)
{
    std::cout << "handling post request ...\n";


    return false;
}


bool ExperimentHandler::handlePut(CivetServer* server, struct mg_connection* conn)
{
    std::cout << "handling put request ...\n";

    cJSON* obj_return = cJSON_CreateObject();
    if (!obj_return) {
        /* insufficient memory? */
        mg_send_http_error(conn, 500, "Server error");
        return false;
    }

    const struct mg_request_info* req_info = mg_get_request_info(conn);
    std::string query;

    if (req_info == NULL) {
        std::cout << "An error occurs when get request info \n";
    }
    else if (req_info->query_string == NULL) {
        std::cout << "No query string in the url" << std::endl;
    }
    else {
        query = std::string(req_info->query_string);
        std::cout << "query is: " << query << std::endl;
        std::string delimiter = "=";
        size_t pos = query.find(delimiter);
        if (pos == std::string::npos) { // no delimiter found
            std::cout << "Wrong URL request format " << std::endl;
            cJSON_AddStringToObject(obj_return, "Error", "Wrong URL request format ");
        }
        else {
            std::string para = query.substr(0, pos);
            std::cout << "para is: " << para << std::endl;
            std::string val = query.erase(0, pos + delimiter.length());
            std::cout << "val is: " << val << std::endl;

            if (0 == str_info.compare(para)) { // get info request
                if (0 == str_scan.compare(val)) {
                    std::cout << "Start to scan" << std::endl;
                    // mqtt: forward cmd to blidatasvc
                    //mqtt.publish("command", val);
                }
                else if (0 == str_stop.compare(val)) {
                    std::cout << "Start to scan" << std::endl;
                    // mqtt: forward cmd to blidatasvc
                    //mqtt.publish("command", val);
                }
                else if (0 == str_lampOn.compare(val)) {
                    std::cout << "Lamp on" << std::endl;
                    // GRPC turn on lamp
                }
                else if (0 == str_lampOff.compare(val)) {
                    std::cout << "Lamp off" << std::endl;
                    // GRPC turn off lamp
                }
            }

        }
    }

    cJSON_AddNumberToObject(obj_return, "exp_status", 0);
    SendJSON(conn, obj_return);
    cJSON_Delete(obj_return);





    return false;

}



