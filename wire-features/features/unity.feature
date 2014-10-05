Feature: Being able to develop with a unit testing framework
  As a developer working on this project
  I want to be able to use a unit-testing framework
  So that that I will be able to confidently practice TDD

  Scenario: Making sure that the framework is installed
    Given I have Unity copied to "unity-master"
    Then Unity is invoked and the test is run
