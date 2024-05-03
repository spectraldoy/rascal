#ifndef PARSE_TREE_H
#define PARSE_TREE_H

#include "visitor.h"
#include "token.h"

class Node {
public:
    virtual void accept(Visitor v) = 0;
};

class NodeOptional : public Node {
public:
    std::unique_ptr<Node> n = nullptr;
    bool present = false;
};

class Goal : public Node {
public:    
    // Either PrefacedBody or Body
    std::unique_ptr<Node> body;
};

class PrefacedBody : public Node {
public:    
    // PrefaceSection
    std::unique_ptr<Node> preface;
    // Body
    std::unique_ptr<Node> body;
};

class Body : public Node {
public:    
    // TcpSection or ServicesSection
    std::unique_ptr<NodeOptional> section;
    // Body
    std::unique_ptr<Node> body;
};

class PrefaceSection : public Node {
public:    
    Token tok_preface;
    Token tok_colon;
    // Q
    std::unique_ptr<Node> lines;
    Token tok_newline;
    Token tok_newline;
};

class TcpSection : public Node {
public:    
    Token tok_tcp;
    Token tok_colon;
    // Lines
    std::unique_ptr<Node> lines;
    Token tok_newline;
    Token tok_newline;
};

class ServicesSection : public Node {
public:    
    Token tok_services;
    Token tok_colon;
    std::unique_ptr<Node> service_lines;
    Token tok_newline;
    Token tok_newline;
};

class Lines : public Node {
public:
    Token tok_tab;
    std::unique_ptr<Node> identifiers;
    Token tok_final_id;
    std::unique_ptr<Node> next_line;
};

class ServiceLines : public Node {
    
};

#endif