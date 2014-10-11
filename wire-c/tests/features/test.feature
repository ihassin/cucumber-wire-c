Feature:
  As a developer of wire
  I want to check that cucumber can communicate with it
  So that I know it's compatible

Scenario: Making sure that wire is running
  Given wire server is running
  When I run this scenario
  Then it responds correctly
