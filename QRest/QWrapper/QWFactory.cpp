#include "QWFactory.h"

namespace QRest
{
	namespace QWrapper
	{
		QResponse* QWFactory::Create(std::string str)
		{
			Json::Reader jr;
			Json::Value jObj;
			jr.parse(str, jObj);
			
			// Schauen welche Art von Response
			// check if done status-->ID
			std::string statusID = jObj["status"]["id"].asString();

			if (statusID == STATUD_ID_DONE) {

				// wenn paramscustomize seed vorhanden --> SIM
				if (jObj["paramsCustomize"]["seed"] == Json::nullValue) {
					
					// RealDone
					
					// Results
					std::list<std::string> labels = std::list<std::string>();
					for (auto itr : jObj["result"]["data"]["p"]["labels"]) {
						labels.push_back(itr.asString());
					}

					std::list<double> values = std::list<double>();
					for (auto itr : jObj["result"]["data"]["p"]["values"]) {
						values.push_back(itr.asDouble());
					}

					QDataP dataP = QDataP(labels, values);
					QData data = QData(dataP, jObj["result"]["data"]["qasm"].asString(), jObj["result"]["data"]["serialNumberDevice"].asString(), jObj["result"]["data"]["time"].asDouble());
					QResult result = QResult(jObj["result"]["date"].asString(), data);

					// Calibration
					// QFridgeParameters
					std::list<std::string> tempvalue = std::list<std::string>();
					if (jObj["calibration"]["fridgeParameters"]["Temperature"] != Json::nullValue) {
						for (auto itr : jObj["calibration"]["fridgeParameters"]["Temperature"]["value"])
						{
							tempvalue.push_back(itr.asString());
						}
					}
					
					QFridgeTemperature temp = QFridgeTemperature(jObj["calibration"]["fridgeParameters"]["Temperature"]["date"].asString(), tempvalue, jObj["calibration"]["fridgeParameters"]["Temperature"]["unit"].asString());

					QFridgeParameters fridgeparams = QFridgeParameters(jObj["calibration"]["cooldownDate"].asString(), temp);

					// Qubit list
					std::list<QQubit> qubits = std::list<QQubit>();

					for (auto itr : jObj["calibration"]["qubits"]) {
						qubits.push_back(
							QQubit(itr["name"].asString()
								, QQubitContent(
									itr["buffer"]["date"].asString()
									, itr["buffer"]["value"].asDouble()
									, itr["buffer"]["unit"].asString()
								)
								, QQubitContent(
									itr["gateTime"]["date"].asString()
									, itr["gateTime"]["value"].asDouble()
									, itr["gateTime"]["unit"].asString()
								)
								, QQubitContent(
									itr["T2"]["date"].asString()
									, itr["T2"]["value"].asDouble()
									, itr["T2"]["unit"].asString()
								)
								, QQubitContent(
									itr["T1"]["date"].asString()
									, itr["T1"]["value"].asDouble()
									, itr["T1"]["unit"].asString()
								)
								, QQubitContent(
									itr["frequency"]["date"].asString()
									, itr["frequency"]["value"].asDouble()
									, itr["frequency"]["unit"].asString()
								)
								, QQubitContent(
									itr["gateError"]["date"].asString()
									, itr["gateError"]["value"].asDouble()
								)
								, QQubitContent(
									itr["readoutError"]["date"].asString()
									, itr["readoutError"]["value"].asDouble()
								)
							)
						);
					}

					// MultiQubitGates list
					std::list<QMultiQubitGates> qubitGates = std::list<QMultiQubitGates>();

					for (auto itr : jObj["calibration"]["multiQubitGates"]) {
						std::list<int> qus = std::list<int>();
						for (auto qu : itr["qubits"]) {
							qus.push_back(qu.asInt());
						}

						qubitGates.push_back(QMultiQubitGates(qus, itr["type"].asString(), QGateError(itr["gateError"]["date"].asString(), itr["gatError"]["value"].asDouble()), itr["name"].asString()));
					}

					// Create calibration object
					QCalibration calibration = QCalibration(jObj["calibration"]["lastUpdateDate"].asString(), fridgeparams, qubits, qubitGates, jObj["calibration"]["version"].asString());

					// Create response object
					QResponse* respRD = new QResponseRealDone(
						jObj["startDate"].asString()
						, jObj["modificationDate"].asInt64()
						, jObj["shots"].asInt()
						, jObj["deleted"].asBool()
						, jObj["userDeleted"].asBool()
						, jObj["userId"].asString()
						, jObj["jobId"].asString()
						, jObj["qasm"].asString()
						, jObj["endDate"].asString()
						, jObj["id"].asString()
						, jObj["deviceId"].asString()
						, result
						, QStatus(
							jObj["status"]["id"].asString()
						)
						, QIP(
							jObj["ip"]["ip"].asString()
							, jObj["ip"]["status"].asString()
							, jObj["ip"]["continent"].asString()
						)
						, calibration
						, jObj["typeCredits"].asString()
						, jObj["time"].asDouble()
					);
					return respRD;
				}
				else {
					// SIM Done


					// Create lists/objects for jsonqasm
					// GateDefinition List
					std::string gateD = NULL;
					for (auto itr : jObj["code"]["jsonQASM"]["gateDefinition"]) {
						gateD = itr.asString();
					}

					// Topology
					// Create list with cregs
					std::list<QReg> cregs = std::list<QReg>();
					for (auto itr : jObj["code"]["jsonQASM"]["topology"]["cregs"]) {
						cregs.push_back(QReg(itr["name"].asString(), itr["size"].asInt()));
					}

					// Create list with qregs
					std::list<QReg> qregs = std::list<QReg>();
					for (auto itr : jObj["code"]["jsonQASM"]["topology"]["cregs"]) {
						qregs.push_back(QReg(itr["name"].asString(), itr["size"].asInt()));
					}

					// Create Object
					QTopology topology = QTopology(
						cregs
						, qregs
						, jObj["code"]["jsonQASM"]["topology"]["topology"]["qasmHeader"].asString()
					);
					
					// Playground List
					std::list<QPlayground> playground = std::list<QPlayground>();
					for (auto itr : jObj["code"]["jsonQASM"]["playground"]) {
						if (itr["gates"] != Json::nullValue) {
							std::list<QGate> qgates = std::list<QGate>();
							for (auto gate : itr["gates"]) {
								std::list<bool> affectedLines;
								QMeasureCreg measureCreg;

								if (gate["affectedLines"] != Json::nullValue) {
									affectedLines = std::list<bool>();
									for (auto lines : gate["affectedLines"]) {
										affectedLines.push_back(lines.asBool());
									}
								}
								else {
									
								}

								if (gate["measureCreg"] != Json::nullValue) {
									measureCreg = QMeasureCreg(gate["measureCreg"]["line"].asInt(), gate["measureCreg"]["bit"].asInt());
								}
								else {
									
								}
								qgates.push_back(QGate(gate["name"].asString(), gate["qasm"].asString(), gate["position"].asInt(), affectedLines, measureCreg));
							}
							playground.push_back(QPlayground(itr["name"].asString(), itr["line"].asInt(), qgates));
						}
						else {
							playground.push_back(QPlayground(itr["name"].asString(), itr["line"].asInt(), std::list<QGate>()));
						}
					}

					// Create JsonQASM Object
					QJsonQASM jqasm = QJsonQASM(
						gateD
						, topology
						, playground
						, jObj["code"]["jsonQASM"]["numberGates"].asInt()
						, jObj["code"]["jsonQASM"]["hasMeasures"].asBool()
						, jObj["code"]["jsonQASM"]["numberColumns"].asInt()
						, jObj["code"]["jsonQASM"]["include"].asString()
					);

					// Qubit list
					std::list<int> resQubit = std::list<int>();
					for (auto itr : jObj["result"]["data"]["p"]["qubits"]) {
						resQubit.push_back(itr.asInt());
					}
					
					// Get label list
					std::list<std::string> resLabel = std::list<std::string>();
					for (auto itr : jObj["result"]["data"]["labels"]) {
						resLabel.push_back(itr.asString());
					}

					// Get value list
					std::list<double> resValues = std::list<double>();
					for (auto itr : jObj["result"]["data"]["values"]) {
						resValues.push_back(itr.asDouble());
					}

					QDataP datap = QDataP(resQubit, resLabel, resValues);
					QData data = QData(
						jObj["result"]["data"]["creg_labels"].asString()
						, datap
						, QAdditionalData(
							jObj["result"]["data"]["additionalData"]["seed"].asString()
						)
						, jObj["result"]["data"]["qasm"].asString()
						, jObj["result"]["data"]["serialNumberDevice"].asString()
						, jObj["result"]["data"]["time"].asDouble()
					);

					QResult result = QResult(jObj["result"]["date"].asString(), data);

					// Create Simulation Object
					QResponse* respSim = new QResponseSim(
						QCode(
							jObj["code"]["type"].asString()
							, jObj["code"]["active"].asBool()
							, jObj["code"]["versionId"].asInt()
							, jObj["code"]["idCode"].asString()
							, jObj["code"]["name"].asString()
							, jqasm
							, jObj["code"]["qasm"].asString()
							, jObj["code"]["codeType"].asString()
							, jObj["code"]["creationDate"].asString()
							, jObj["code"]["deleted"].asBool()
							, jObj["code"]["orderDate"].asInt64()
							, jObj["code"]["userDeleted"].asBool()
							, jObj["code"]["isPublic"].asBool()
							, jObj["code"]["id"].asString()
							, jObj["code"]["userId"].asString()
						)
						, QParamsCustomize(
							jObj["paramsCustomize"]["seed"].asInt64()
						)
						, jObj["time"].asDouble() // Könnte mit der länge eng werden hat 16 Nachkommastellen
						, jObj["deviceRunType"].asString()
						, jObj["startDate"].asString()
						, jObj["modificationDate"].asInt64()
						, jObj["shots"].asInt()
						, jObj["deleted"].asBool()
						, jObj["userDeleted"].asBool()
						, jObj["userId"].asString()
						, jObj["qasm"].asString()
						, jObj["endDate"].asString()
						, jObj["id"].asString()
						, jObj["deviceId"].asString()
						, jObj["codeId"].asString()
						, result
						, QStatus(
							jObj["status"]["id"].asString()
						)
						, QIP(
							jObj["ip"]["ip"].asString()
							, jObj["ip"]["country"].asString()
							, jObj["ip"]["continent"].asString()
						)
					);
					
					// Return simulation object
					return respSim;
				}
			}
			else if (statusID == STATUD_ID_WORKING) {
				// Real Undone
				QResponse* respUndone = new QResponseRealUndone(
					jObj["startDate"].asString()
					, jObj["modificationDate"].asInt64()
					, jObj["shots"].asInt()
					, jObj["deleted"].asBool()
					, jObj["userDeleted"].asBool()
					, jObj["userId"].asString()
					, jObj["jobId"].asString()
					, jObj["qasm"].asString()
					, jObj["id"].asString()
					, QStatus(
						jObj["status"]["id"].asString()
					)
					, QIP(
						jObj["ip"]["ip"].asString()
						, jObj["ip"]["country"].asString()
						, jObj["ip"]["continent"].asString()
					)
					, jObj["typeCredits"].asString()
				);
				
				return respUndone;
			}
			else {
				//EXC or something else
				throw std::logic_error("Not implemented");
			}
		}
	}
}