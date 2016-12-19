Feature:
  Testing the page for creating a new site.

  @api @vsite
  Scenario: Make sure all types of a site are presented to an authenticated user.
    Given I am logging in as "michelle"
     When I visit "site/register"
     Then I should see the options "Department Site,Personal Site,Project Site" under "bundle"
