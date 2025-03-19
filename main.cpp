#include <bits/stdc++.h>

class BullyAlgorithm
{
private:
    int nodes;
    bool isCoordinator;

public:
    BullyAlgorithm(int nodes)
    {
        this->nodes = nodes;
        this->isCoordinator = false;
    }

    int getNodeID()
    {
        return this->nodes;
    }

    void setCoordinator(bool coordinator)
    {
        this->isCoordinator = coordinator;
    }

    void initElection(std::vector<BullyAlgorithm> &nodes)
    {
        std::cout << "Election Initiated by node " << this->nodes << std::endl;

        for (BullyAlgorithm &Node : nodes)
        {
            if (Node.getNodeID() > this->nodes)
            {
                Node.receiveElectionMessage(*this);
            }

            if (!isCoordinator)
            {
                becomeCoordinator();
            }
        }
    }

    void receiveElectionMessage(BullyAlgorithm Node)
    {
        std::cout << "Received Election Message from node " << Node.getNodeID() << std::endl;
        if (this->nodes > Node.getNodeID())
        {
            std::cout << "Node  " << this->nodes << " the new Coordinator" << std::endl;
            Node.receiveResponse(*this);
        }
    }

    void receiveResponse(BullyAlgorithm Node)
    {
        std::cout << "Received Response from node " << Node.getNodeID() << std::endl;
    }

    void becomeCoordinator()
    {
        std::cout << "Node " << this->nodes << " is now a Coordinator Node" << std::endl;
        this->isCoordinator = true;
    }
};

class RingAlgorithm
{
private:
    int nodeID;
    bool isCoordinator;
    RingAlgorithm *nextNode;
    std::vector<std::string> processLog;

public:
    RingAlgorithm(int nodeID)
    {
        this->nodeID = nodeID;
        this->isCoordinator = false;
        this->nextNode = nullptr;
    }

    int getNodeID()
    {
        return this->nodeID;
    }

    void setNextNode(RingAlgorithm *next)
    {
        this->nextNode = next;
    }

    void setCoordinator(bool coordinator)
    {
        this->isCoordinator = coordinator;
    }

    void initElection()
    {
        logState("Election Initiated by node " + std::to_string(this->nodeID));
        // Start the election by sending message to the next node
        this->nextNode->receiveElectionMessage(this);
    }

    void receiveElectionMessage(RingAlgorithm *fromNode)
    {
        logState("Node " + std::to_string(this->nodeID) + " received Election Message from node " + std::to_string(fromNode->getNodeID()));

        // Pass the message along with the nodeID to the next node
        if (this->nodeID > fromNode->getNodeID())
        {
            logState("Node " + std::to_string(this->nodeID) + " passes message with nodeID " + std::to_string(this->nodeID) + " to the next node.");
            this->nextNode->receiveElectionMessage(this); // Forward the message to the next node
        }
        else
        {
            // If we received the message back, we are the coordinator
            logState("Node " + std::to_string(fromNode->getNodeID()) + " is the new Coordinator.");
            fromNode->becomeCoordinator();
        }
    }

    void becomeCoordinator()
    {
        logState("Node " + std::to_string(this->nodeID) + " is now the Coordinator.");
        this->isCoordinator = true;
    }

    void logState(const std::string &message)
    {
        // Log the current state for the node
        processLog.push_back(message);
    }

    void printProcessLog()
    {
        std::cout << "Process log for node " << this->nodeID << ":\n";
        for (const auto &entry : processLog)
        {
            std::cout << entry << std::endl;
        }
        std::cout << "----------------------------\n";
    }
};

int main()
{
    BullyAlgorithm node1(1);
    BullyAlgorithm node2(2);
    BullyAlgorithm node3(3);
    BullyAlgorithm node4(4);
    BullyAlgorithm node5(5);

    std::vector<BullyAlgorithm> nodes;
    nodes.push_back(node1);
    nodes.push_back(node2);
    nodes.push_back(node3);
    nodes.push_back(node4);
    nodes.push_back(node5);

    int index;

    while (true)
    {
        std::cout << "\nThere are five nodes in the system. The nodes are numbered from 1 to 5." << std::endl;
        std::cout << "Select a Node to shut down ";
        std::cin >> index;
        if (index >= 1 && index <= 5)
        {
            if (index == 5)
            {
                std::cout << "Node 5 is the highest coordinator which failed so Node 4 will become the new coordinator." << std::endl;
            }
            else
            {
                nodes.at(index - 1).setCoordinator(false);
                nodes.at(index - 1).initElection(nodes);
            }
        }
        else
        {
            std::cout << "\nBreaking the Election loop..." << std::endl;
            break;
        }
    }

    return 0;
}