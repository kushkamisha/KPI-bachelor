#Author: your.email@your.domain.com
#Keywords Summary :
#Feature: List of scenarios.
#Scenario: Business rule through list of steps with arguments.
#Given: Some precondition step
#When: Some key actions
#Then: To observe outcomes or validation
#And,But: To enumerate more Given,When,Then steps
#Scenario Outline: List of steps for data-driven as an Examples and <placeholder>
#Examples: Container for s table
#Background: List of steps run before each of the scenarios
#""" (Doc Strings)
#| (Data Tables)
#@ (Tags/Labels):To group Scenarios
#<> (placeholder)
#""
## (Comments)
#Sample Feature Definition Template
@tag
Feature: Title of your feature
Background:
  Given I want to login to the circus page

  @tag1
  Scenario Outline: Title of your scenario outline
    Given Search for the elephants performance
    When I book a <quantity> of tickets
    Then I see a <total> price

    Examples: 
      | quantity | total |
      | 2        | 200   |
      | 3        | 300   |