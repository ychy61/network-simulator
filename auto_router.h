#ifndef AUTO_ROUTER_H
#define AUTO_ROUTER_H

#include "host.h"
#include "link.h"
#include "router.h"
#include "service.h"
#include <algorithm>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <vector>

// AutoRouter 클래스는 Router 클래스를 상속받아 자동 라우팅 기능을 구현한다.
class AutoRouter : public Router
{
private:
    // 라우터의 이름을 반환하는 함수
    virtual std::string name() override { return "AutoRouter"; }

public:
    // 노드와 링크를 기반으로 라우팅 테이블을 계산하는 함수
    void calculate(const std::vector<Node *> &nodes, const std::vector<Link *> &links)
    {
        std::map<Node *, double> delayToNode; // 각 노드까지의 지연 시간을 저장
        std::map<Node *, Link *> optimalLinkToNode; // 최적 경로의 링크를 저장

        // 모든 노드에 대해 초기 지연 시간과 링크를 무한대와 nullptr로 초기화
        for (auto &node : nodes)
        {
            delayToNode[node] = std::numeric_limits<double>::infinity();
            optimalLinkToNode[node] = nullptr;
        }

        // 시작 노드(this)의 지연 시간을 0으로 설정
        delayToNode[this] = 0.0;

        // 우선순위 큐를 지연 시간이 작은 순으로 정렬하기 위한 비교 함수
        auto delayComparator = [&](Node *left, Node *right) { return delayToNode[left] > delayToNode[right]; };
        std::priority_queue<Node *, std::vector<Node *>, decltype(delayComparator)> nodesQueue(delayComparator);

        // 현재 라우터(this)에 연결된 링크를 통해 이웃 노드를 우선순위 큐에 추가
        for (auto &link : this->linkTable())
        {
            Node *connectedNode = link->other(this);
            delayToNode[connectedNode] = link->delay();
            optimalLinkToNode[connectedNode] = link;
            nodesQueue.push(connectedNode);
        }

        // 우선순위 큐를 사용하여 네트워크의 모든 노드를 처리
        while (!nodesQueue.empty())
        {
            Node *currentNode = nodesQueue.top();
            nodesQueue.pop();

            // 현재 노드에 연결된 모든 링크를 검사하여 더 짧은 경로를 찾으면 업데이트
            for (auto &link : currentNode->linkTable())
            {
                double newTotalDelay  = delayToNode[currentNode] + link->delay();
                Node *neighbor = link->other(currentNode);

                if (delayToNode[neighbor] > newTotalDelay )
                {
                    delayToNode[neighbor] = newTotalDelay;
                    optimalLinkToNode[neighbor] = optimalLinkToNode[currentNode];
                    nodesQueue.push(neighbor);
                }
            }
        }

        // 라우팅 테이블을 최적의 경로 정보로 갱신
        this->routingTable_.clear();
        for (auto &entry : optimalLinkToNode)
        {
            Node *destinationNode  = entry.first;
            Link *nextHopLink  = entry.second;
            if (nextHopLink  == nullptr || destinationNode  == this)
            {
                continue;
            }
            if (Host *host = dynamic_cast<Host *>(destinationNode))
            {
                this->routingTable_.push_back({host->address(), nextHopLink });
            }
        }
    }
};

#endif
