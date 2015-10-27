

/*######OPCODE##########*/
typedef uint8_t OpCode;
#define READDATA 		((uint8_t)0x00) 		//invia misurazione al centro di controllo 					###	Centro Controllo -> Nodo Sensore
#define CONFIGSENSOR 	((uint8_t)0x01) 		//configurazione sensore 									###	Centro Controllo -> Nodo Sensore
#define DATA 			((uint8_t)0x02)			//dato di misurazione										###	Nodo Sensore -> Centro Controllo
#define JOIN			((uint8_t)0x03)			//join nodo, fornisce la chiave personale del nodo e l'id	### Centro Controllo <- Nodo centrale
#define REPLYJOIN		((uint8_t)0x04)			//replyjoin risponde al nodo con la chiave condivisa		### Centro Controllo -> Nodo Centrale
#if USE_LOG == 1
#define LOG          ((uint8_t)0x06)
#endif
#define SYNC         ((uint8_t)0x07)  //richiesta di sincronizzazione da parte di un nodo della rete
/*#####################*/




typedef struct __attribute__((aligned(1),packed)) payload  {
	uint8_t id; 		//id sensore
	int16_t val;		//valore
	uint8_t alarm;		//allarme
	int32_t ht;			//high th.shold
	int32_t lt;			//low  th.shold
	int16_t period;		//periodo
	int8_t  priority;	//priorit��
}Payload;

//128 bit application package

typedef struct netPackage{
	OpCode 	code;
	Payload	payload;
} NetPackage;

typedef struct __attribute__((aligned(1),packed)) {
  uint8_t opCode;
  uint8_t sensorID;      // ID sensore
  int16_t value;         // Valore
  uint8_t alarm;         // Allarme
  int32_t highThreshold; // High threshold
  int32_t lowThreshold;  // Low  threshold
  int16_t period;        // Periodo
  int8_t  priority;      // Priorit���
} NetMessage;



#ifdef NODOCENTRALE
//###################################################
//Pacchetti Centro controllo <-> Nodo Centrale
//##################################################

#define DIMPACK 232 //Dimensione

typedef struct readDataPacketType {
  uint16_t nodeAddress;
  uint8_t  sensorID;
} ReadDataPacketType;

typedef struct dataPacketType {
  uint16_t nodeAddress;
  uint8_t  sensorID;
  int32_t  value;
  uint8_t  alarm;
}DataPacketType;

typedef struct configSensorType {
  uint16_t nodeAddress;
  uint8_t  sensorID;
  int32_t  value;
  uint8_t  alarm;
  int32_t  highThreshold;
  int32_t  lowThreshold;
  int16_t  period;
  int8_t   priority;
} ConfigSensorType;

typedef struct nodeIDType {
  uint64_t id0;
  uint32_t id1;
} NodeIDType;

typedef struct secretKeyType {
  uint64_t sk0;
  uint64_t sk1;
} SecretKeyType;

typedef struct canJoinPacketType {
  NodeIDType nodeID;
} CanJoinPacketType;

typedef struct canJoinReplyPacketType {
  NodeIDType nodeID;
  SecretKeyType secretKey;
} CanJoinReplyPacketType;



typedef struct nodeMessage{
	uint8_t code;
	union {
		ReadDataPacketType 		readDataPacket;
		DataPacketType 			dataPacket;
		ConfigSensorType		configSensor;
		CanJoinPacketType		canJoinPacket;
		CanJoinReplyPacketType	canJoinReplyPacket;
	};
} NodeMessage;
#endif

