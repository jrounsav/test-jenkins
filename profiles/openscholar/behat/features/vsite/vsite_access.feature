Feature:
  Testing the viste access.

  @api @vsite
  Scenario: Testing the Vsite access to the views.
    Given I visit "news"
      And I should see "I opened a new personal"
      And I should see "Lou's site news"
      And I should see "More tests to the semester"
     When I visit "john/news"
     Then I should see "I opened a new personal"
      And I should see "More tests to the semester"
      And I should not see "Lou's site news"
     When I visit "als/news"
     Then I should not see "I opened a new personal"
      And I should not see "More tests to the semester"
      And I should see "Lou's site news"

  @api @vsite
  Scenario: Testing the robot txt when site is private
    Given I am logging in as "john"
      And I visit "lincoln/cp/settings"
      And I select the radio button named "vsite_private" with value "1"
      And I press "edit-submit"
      And I visit "lincoln/robots.txt"
      And I should get:
      """
      User-agent: *
Disallow: /
Disallow: /einstein/
Disallow: /lincoln/
      """
     When I visit "lincoln/cp/settings"
      And I press "edit-submit"
      And I visit "lincoln/robots.txt"
     Then I should get:
    """
    User-agent: *
Disallow: /
Disallow: /einstein/
Disallow: /lincoln/
      """
    And I visit "lincoln/cp/settings"
    And I select the radio button named "vsite_private" with value "0"
    And I press "edit-submit"
