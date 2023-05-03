#ifndef _matrixclient_h_
#define _matrixclient_h_

#include <string>
#include <vector>
#include <switch.h>
#include <jansson.h>
#include <map>
#include <curl/curl.h>

namespace Matrix {

class Store {
public:
	virtual void setSyncToken(std::string token) = 0;
	virtual std::string getSyncToken() = 0;
	virtual void setFilterId(std::string filterId) = 0;
	virtual std::string getFilterId() = 0;
};

struct RoomInfo {
	std::string name;
	std::string topic;
	std::string avatarUrl;
};

struct MemberInfo {
	std::string displayname;
	std::string avatarUrl;
};

struct ExtraRoomInfo {
	std::string canonicalAlias;
	std::map<std::string, MemberInfo> members;
};

typedef void (*eventCallback)(std::string roomId, json_t* event);
typedef void (*roomInfoCallback)(std::string roomId, RoomInfo info);
typedef void (*roomLimitedCallback)(std::string roomId, std::string prevBatch);

class Client {
private:
	std::string hsUrl;
	std::string token;
	Store* store;
	std::string userIdCache = "";
	int requestId = 0;
	bool stopSyncing = false;
	bool isSyncing = false;
	Thread syncThread;
	struct {
		eventCallback event = NULL;
		eventCallback leaveRoom = NULL;
		eventCallback inviteRoom = NULL;
		roomInfoCallback roomInfo = NULL;
		roomLimitedCallback roomLimited = NULL;
	} callbacks;
	void processSync(json_t* sync);
	void registerFilter();
	json_t* doSync(std::string token, std::string filter, u32 timeout, CURLcode* res);
	json_t* doRequest(const char* method, std::string path, json_t* body = NULL, u32 timeout = 5, CURLcode* retRes = NULL);
	json_t* doRequestCurl(const char* method, std::string url, json_t* body, u32 timeout, CURLcode* retRes);
public:
	Client(std::string homeserverUrl, std::string matrixToken = "", Store* clientStore = NULL);
	std::string getToken();
	bool login(std::string username, std::string password);
	void logout();
	std::string getUserId();
	std::string resolveRoom(std::string alias);
	std::vector<std::string> getJoinedRooms();
	RoomInfo getRoomInfo(std::string roomId);
	ExtraRoomInfo getExtraRoomInfo(std::string roomId);
	MemberInfo getMemberInfo(std::string userId, std::string roomId = "");
	std::string getRoomName(std::string roomId);
	std::string getRoomTopic(std::string roomId);
	std::string getRoomAvatar(std::string roomId);
	std::string getCanonicalAlias(std::string roomId);
	void sendReadReceipt(std::string roomId, std::string eventId);
	void setTyping(std::string roomId, bool typing, u32 timeout = 30000);
	std::string sendEmote(std::string roomId, std::string text);
	std::string sendNotice(std::string roomId, std::string text);
	std::string sendText(std::string roomId, std::string text);
	std::string sendMessage(std::string roomId, json_t* content);
	std::string sendEvent(std::string roomId, std::string eventType, json_t* content);
	json_t* getStateEvent(std::string roomId, std::string type, std::string stateKey);
	std::string sendStateEvent(std::string roomId, std::string type, std::string stateKey, json_t* content);
	std::string redactEvent(std::string roomId, std::string eventId, std::string reason = "");
	void startSyncLoop();
	void stopSyncLoop();
	void setEventCallback(eventCallback cb);
	void setLeaveRoomCallback(eventCallback cb);
	void setInviteRoomCallback(eventCallback cb);
	void setRoomInfoCallback(roomInfoCallback cb);
	void setRoomLimitedCallback(roomLimitedCallback cb);
	void syncLoop();
};

}; // namespace Matrix

#endif // _matrixclient_h_
