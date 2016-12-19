Feature:
  Testing the news tab.

  @api @features_second
  Scenario: Test the News tab
    Given I visit "john"
     When I click "News"
      And I click "I opened a new personal"
     Then I should see "This is a new site generated via the vsite options in open scholar."
