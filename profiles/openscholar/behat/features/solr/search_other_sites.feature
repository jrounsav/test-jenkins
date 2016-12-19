Feature:
  Testing search function using apache solr for searching in other sites
  (selected sites and/or subsites).

  @api @solr
  Scenario: Check search results are from the selected list of sites.
    Given I am logging in as "john"
      And I add to the search results the sites "obama"
     When I search for "john" in the site "john"
     Then I click on "Obama (1)" under facet "Filter by other sites"
          # Result form "john"
      And I should not see "Who was JFK?"
          # Result form "obama"
      And I should see "Me and michelle obama"

  @api @solr
  Scenario: Check search results are from the selected list of subsites.
    Given I am logging in as "alexander"
      And I add to the search results the site's subsites
     When I search for "blog" in the site "edison"
     Then I click on "Tesla (1)" under facet "Filter by other sites"
          # Result form "tesla"
      And I should see "Tesla's blog"

  @api @solr
  Scenario: Verify that other site widget won't show if it's empty.

    Given I am logging in as "john"
      And I add to the search results the sites "obama"
     When I search for "music" in the site "john"
     Then I should not see "Filter by other sites"
