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
@Cart
Feature: Cart quantity change causes correct "totals" recalculation
Background:
  Given Login page of the circus is opened

  @CartQuantity
  Scenario Outline: Title of your scenario outline
    Given I search for a performance by a key word elephants and add tickets to a cart
    When I set the <quantity> of items in the list and add them to a cart
    Then I get recalculated <total>

    Examples: 
      | quantity | total |
      | 2        | 200   |